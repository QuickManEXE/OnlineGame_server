#pragma once
#include "../GLLibrary.h"

#ifdef USE_ATHOR_MODEL
#include "pugixml.hpp"
#endif
#include <list>
#define A3MVERSION	0x100
namespace A3M {
	/*
		ノードの種類
	*/
	enum E_NODE_TYPE {
		eNode,	//通常
		eMesh,	//メッシュ
	};
	enum E_VERTEX_TYPE {
		eStaticMesh,
		eSkinMesh,
	};
};

class CA3MMesh;
/*
	ノードクラス
*/
class CA3MNode {
public:
protected:
	int	 m_no;			//ノード番号
	int m_bone_no;
	char m_name[NAME_STR_SIZE];
	A3M::E_NODE_TYPE m_node_type;	//ノードの種類
	CMatrix m_matrix;
	CMatrix m_offset;
	//CMatrix m_bind_pose_inv;
	//CMatrix *mp_bone;
	CMatrix m_local_matrix;
	CVector3D m_pos;
	CQuaternion m_rot;
	CVector3D m_scale;
	bool m_bind;
	CMatrix m_bind_matrix;
	bool m_visibility;
	char m_euler_order[3];		//回転行列順番
	CA3MMesh* mp_mesh;
	CA3MNode* mp_child;	//子フレーム
	CA3MNode* mp_parent;	//親フレーム
	CA3MNode* mp_next;		//兄弟フレーム
	CA3MNode* mp_prev;
public:
	CA3MNode();
	CA3MNode(int no, const char* name);

	CA3MNode(const CA3MNode& n);
	virtual ~CA3MNode();
	char* GetName() {
		return m_name;
	}
	int GetNo() { return m_no;}
	A3M::E_NODE_TYPE GetNodeType() { return m_node_type;}

	void SetMatrix(const CMatrix &m) {		
		m_matrix = m;
	}
	CMatrix GetMatrix() const{		
		return m_matrix;
	}

	/*
	  名前からノードを取得
	*/
	static CA3MNode* FindNode(const char* name, CA3MNode* n);
	/*
	  番号からノードを取得
	*/
	static CA3MNode* FindNode(const int no, CA3MNode*n);

	virtual void Release();
	/*
	  デバッグ用
	*/
	static void PintMatrix(CA3MNode* n);
	static void PrintNode(CA3MNode* n,int level);
	void SetVisibility(bool f) { m_visibility = f; }

	virtual void Draw(){};

	friend class CModelA3M;

};

class CA3MColl {
public:
	CVector3D m_max;
	CVector3D m_min;
	CVector3D m_cut;
	CVector3D m_length;
	CVector3D* m_colmin;
	CVector3D* m_colmax;
public:
	CA3MColl();
	~CA3MColl();
	int GetIndex(int x, int y, int z) const{
		return x + (z * m_cut.ix) + (y * m_cut.iz * m_cut.ix);
	}
	void CalcRange(CVector3D* min, CVector3D* max,const CAABB aabb)const;
};
/*
ポリゴンクラス
マテリアル毎にまとめる
*/
class CA3MPoly {
public:
	unsigned int*	mp_use_skin;
	MY_VERTEX*		mp_vertex;
	unsigned int	m_vertex_cnt;
	unsigned int	m_material;
	GLuint			m_buffer;
//	GLuint			m_vao;
	const CA3MColl*	m_col_cut;
	unsigned long* m_colmask;
	std::vector<int>* m_colIdex;
public:
	CA3MPoly(unsigned int* use_skin);
	~CA3MPoly();
	int Load(const char* buf);
	/*
	描画
	*/
	void Draw(const CShader* shader);

	void CreateCollisionIndex(const CA3MColl* c);
	bool CollisionRay(CVector3D* c, CVector3D* n, const CVector3D& s, const CVector3D& e, const CVector3D& dir, float* pLength, const CVector3D& start, const CVector3D& end);
	int CollisionSphere(CCollTriangle* out, const CVector3D& center, float radius, int maxcnt, const CVector3D& start, const CVector3D& end);
	int CollisionCupsel(CCollTriangle* out, const CVector3D& top, const CVector3D& bottom, float radius, int maxcnt, const CVector3D& start, const CVector3D& end);
	
};
/*
/*
  [Mesh]
*/
class CA3MMesh {
public:
	std::list<CA3MPoly*> m_poly_list;
	unsigned long m_poly_cnt;
	const CA3MColl* m_col_cut;
	bool *mp_enable_animation;
	unsigned int m_use_skin;
public:
	CA3MMesh(bool* p_enable_animation);
//	CA3MMesh(const CA3MMesh& mesh);
	~CA3MMesh();
	CA3MMesh& operator = (const CA3MMesh& mesh);
	int Load(const char* buf);
	virtual void Release();
	/*
	描画
	*/
	void Draw(std::vector<CMaterial*>& materialList, const CShader* shader);
	void CreateCollisionIndex(const CA3MColl* c);

	bool CollisionRay(CVector3D* c, CVector3D* n, const CVector3D& s, const CVector3D& e, float* pLength, CMatrix& matrix);
	int CollisionSphere(CCollTriangle* out, const CVector3D& center, float radius, int maxcnt, CMatrix& matrix);
	int CollisionCupsel(CCollTriangle* out, const CVector3D& top, const CVector3D& bottom, float radius, int maxcnt, CMatrix& matrix);
	friend class CA3MMesh;

};

struct CA3MAnimationKey {
	int m_frame;						//0
	union {
		CMatrix m_matrix;
		struct {
			CVector3D m_position;		//1,2.3
			CQuaternion m_rotation;		//4,5,6,7
			CVector3D m_scale;			//8,9,10
			float pat[6];				//11,12,13,14,15,16
		};
	};
	CA3MAnimationKey():m_frame(0){}
	CA3MAnimationKey(const CVector3D& pos,const CQuaternion& rotation, const CVector3D& scale):
		m_frame(0),m_position(pos),m_rotation(rotation),m_scale(scale) {}
};
struct CA3MAnimationAction {
	int m_size;
	CA3MAnimationKey* m_keys;
};

struct CA3MAnimationSet {
	char m_name[NAME_STR_SIZE];
	float m_fps;
	union {
		int m_time[2];
		struct {
			int m_start;
			int m_end;
		};
	};
	int m_end_base;
	std::map<int, CA3MAnimationAction*> m_bones;
};
/*
	アニメーション
*/
class CA3MAnimation {

private:


	int m_jam;
	float m_speed;
	bool m_loop;
	float m_frame;
	std::vector<CA3MAnimationSet*> *mp_animation_list;
public:
	CA3MAnimation(std::vector<CA3MAnimationSet*>* animation_list);
	~CA3MAnimation();
	void ChangeAnimation(int jam, bool loop, bool check, float time, int blend_frame);
	void UpdateAnimation();
	bool isAnimationEnd();
	int GetAnimationJam();
	void SetAnimationSpeed(float s);
	int GetAnimationFrame();
	friend class CModelA3M;
};
/*
	A3M用モデルファイル
*/
class CModelA3M : public CModel {
private:
	std::vector<CMaterial*> m_material_list;
	CA3MNode* mp_root;
	int			m_bone_num;
	CMatrix* m_bone_matrix;
	CA3MAnimation* m_animation;
	int		m_animation_size;
	std::vector<CA3MAnimationSet*> m_animation_list;
	std::vector<CA3MNode*> m_mesh_list;
	//A3M::E_VERTEX_TYPE	m_vertex_type;
	CA3MColl	*m_col_cut;

	bool	m_enable_animation;
	//CAnimation* animation;
	CA3MNode* LoadNode(FILE* fp, CA3MNode* parent, CA3MNode* prev);
	int LoadAnimation(FILE* fp);
	void DrawMesh(CA3MNode* node, const CMatrix& view_matrix);
	void ReleaseNode(CA3MNode* node);
	int WriteNode(FILE* fp, CA3MNode* node);
	int WriteAnimation(FILE* fp);
	void LeapAnimationKey(float* key, int start, int end, float vs, float ve, int max, int step);
	void LeapAnimationKey(CA3MAnimationKey* key, int start, int end);

#ifdef USE_ATHOR_MODEL
	CA3MNode* DuplicateFBXMesh(FbxNode* pNode,int& no,CA3MNode* parent, CA3MNode* prev);
	bool DuplicateFBXAnimation(FbxNode* pNode, const CModelFBX::AnimationInfo* info,int no);
	CA3MNode* DuplicateXMesh(CFrameBone* pNode, int& no, CA3MNode* parent, CA3MNode* prev);
	bool DuplicateXAnimation(CXAnimationSet* set, float fps);
	struct SMeshNodeSet {
		pugi::xml_node mp_toy_node;
		CA3MNode* mp_node;
		SMeshNodeSet(pugi::xml_node& t, CA3MNode* n) :mp_toy_node(t){
			mp_node = n;
		}
	};

	static void ReadMatrix(CMatrix* mat, pugi::xml_node& pNode);
	static void ReadMatrix(CA3MNode* node, pugi::xml_node pNode);
	std::vector<SMeshNodeSet> m_toy_mesh_list;
	void LoadToyAnimationSet(pugi::xml_node& pNode,CA3MAnimationSet *set);
	void LoadToyAnimation(pugi::xml_node& pNode);
	void LoadToyMesh(pugi::xml_node& pNode, CA3MNode* node, CA3MColl* col_cut);
	void LoadToyMaterial(pugi::xml_node& pNode);
public:
	CA3MNode* LoadToyNode(pugi::xml_node& pNode, int& no,int &bone_no, CA3MNode* parent, CA3MNode* prev);
	bool LoadToyModel(const char* file);


private:
#endif
	void CalcBoneMatrix(CA3MNode *node);
	void CreateCollisionIndex(int cntx,int cuty,int cutz);

	CA3MNode* DuplicateNode(CA3MNode* pNode, CA3MNode* parent, CA3MNode* prev);
	void OutputFrameInfo(FILE* fp, CA3MNode* node, int depth);
public:
	CModelA3M();
	~CModelA3M();
	CModelA3M(const CModelA3M& m);
	void operator = (const CModelA3M& m);
	CModelA3M(const CModelObj& m);
#ifdef USE_ATHOR_MODEL
	CModelA3M(const CModelX& m);
	CModelA3M(const CModelFBX& m);
	bool AddAnimationFBX(const char* filepath);
	bool AddAnimationX(const char* filepath);
#endif
	void RemoveAnimation(int jam);

	void Release();
	/*
	ファイルからモデルを構築
	*/
	bool Load(const char* filePath,int cut_x,int cut_y,int cut_z);
	

	void Write(const char* filePath);
	/*
	描画
	*/
	void Render(CMatrix& m);


	void Render();

	void UpdateMatrix();

	/*!
		@brief	指定の行列で各ボーンを更新する
		@retval	無し
	**/
	void UpdateMatrix(CMatrix& m);


	/*!
	@brief	アニメーション更新
	@retval	無し
**/
	void UpdateAnimation();
	/*!
		@brief　アニメーション終了判定
		@retval	true:終了
	**/
	bool isAnimationEnd();
	/*!
		@brief	アニメーションの番号を取得
		@retval	再生中番号（0〜）
	**/
	int GetAnimationJam();
	/*!
		@brief	アニメーションの速度再生速度変更
		@retval	無し
	**/

	void SetAnimationSpeed(float s);
	/*!
		@brief	アニメーション切り替え
		@param	jam				[in] アニメーション番号
		@param	loop			[in] アニメーションループフラグ
		@param	check			[in] 既に再生中かチェック
		@param	frame			[in] 切り替え補間時間
		@retval	無し
	**/

	void ChangeAnimation(int jam, bool loop = true, bool check = true, float time = 0, int blendFrame = 5);
	/*!
		@brief	アニメーションの現在フレームを取得
		@retval	フレーム
	**/

	float GetAnimationFrame();

	/*!
		@brief	アニメーションの数を取得
		@retval	アニメーションの数
	**/
	int GetAnimationSize() const;


	/*!
	@brief	ボーンを指定の方向へ向ける
	@param	no			[in] ボーン番号
	@param	mat			[in] 回転行列
	**/
	void BindFrameMatrix(int no, const CMatrix& mat);
	/*!
	@brief	ボーンを指定の方向へ向ける
	@param	no			[in] ボーン名前
	@param	mat			[in] 回転行列
	**/
	void BindFrameMatrix(const char* name, const CMatrix& mat);


	/*!
	@brief	ボーンの指定方向への固定を解除
	@param	no			[in] ボーン番号
	**/
	void UnbindFrameMatrix(int no);
	/*!
	@brief	ボーンの指定方向への固定を解除
	@param	no			[in] ボーン名前
	**/
	void UnbindFrameMatrix(const char* name);

	/*
		ノードの行列を取得
	 */
	CMatrix GetFrameMatrix(const char* name, bool local = false) const;
	/*
	　ボーンの行列を取得
	 */
	CMatrix GetFrameMatrix(int no, bool local = false) const;


	/*!
	@brief	指定のノードを取得
	@param	no				[in] ノード番号
	@retval	ノードのポインタ
	**/
	CA3MNode* GetNode(int no) const;


	/*!
	@brief	指定のノードを取得
	@param	name			[in] ノードの名前
	@retval	ノードのポインタ
	**/
	CA3MNode* GetNode(const char* name) const;


	/*!
	@brief	マテリアルの取得
	@param	no				[in] マテリアル番号
	@retval	マテリアルのポインタ
	**/
	CMaterial* GetMaterial(int no) const;


	/*!
	@brief	マテリアル数の取得
	@param	no				[in] マテリアル番号
	@retval	マテリアルのポインタ
	**/
	int GetMaterialSize() const {
		return m_material_list.size();
	}



	/*!
	@brief	線分とモデルの判定
	@param	c				[out] 接触地点
	@param	s				[in] 線分の開始地点
	@param	e				[in] 線分の終了地点
	@retval	true:接触　false:非接触
	**/
	bool CollisionRay(CVector3D* c, CVector3D* n, const CVector3D& s, const CVector3D& e)const;


	/*!
	@brief	球とモデルの判定
	@param	out				[out] 接触データ
	@param	center			[in] 球の中心
	@param	radius			[in] 球の半径
	@retval	接触ポリゴン数
	**/
	int CollisionSphere(CCollTriangle* out, const CVector3D& center, float radius, int maxcnt = 64)const;



	/*!
	@brief	カプセルとモデルの判定
	@param	out				[out] 接触データ
	@param	top				[in] カプセルの天井
	@param	bottom			[in] カプセルの底
	@param	radius			[in] 球の半径
	@retval	接触ポリゴン数
	**/
	int CollisionCupsel(CCollTriangle* out, const CVector3D& top, const CVector3D& bottom, float radius, int maxcnt = 64)const;


	/*!
	@brief	ボーンの階層構造をファイルへ出力する
	@param	file_name		[in] 書き込み先
	@retval	接触ポリゴン数
	**/
	void OutputFrameInfo(const char* file_name);



	int GetBoneSize() const { return m_bone_num; }
	bool LoadTexture(const char* filepath, int materil_num);
	CA3MAnimationSet* GetAnimationSet(int jam) {
		return m_animation_list[jam];
	}
	void SwapAnimationSet(int a, int b);

	CA3MAnimation* GetAnimation() {
		return &m_animation[0];
	}
	friend class CModelA3M;

};