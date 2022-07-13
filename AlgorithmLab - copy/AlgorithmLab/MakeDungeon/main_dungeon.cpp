#include <windows.h>
#include<stdio.h>
#include <assert.h>
#include<vector>
#include"DTL.hpp"

#define MAP_WIDTH 64
#define MAP_HEIGHT 64

template <typename T> T Rand(T min, T max) {
    return min + ((max - min) * rand() / RAND_MAX);
}


//頂点データ
struct Point {
    int x; int y;
    Point(){
        x = 0; y = 0;
    }
    Point(int x, int y) {
        this->x = x; this->y = y;
    }
};


//矩形データ
class GridRect {
public:
    int x, y;
    int width, height;
    int left, top, right, bottom;
    GridRect() {
        x = 0; y = 0; width = 1; height = 1;
        left = 0; top = 0; right = 0; bottom = 0;
    }
    GridRect(Point pos, int width, int height) {

        this->x = pos.x; this->y = pos.y;
        this->width = width; this->height = height;
        this->left = pos.x; this->top = pos.y; 
        this->right = pos.x+width-1; this->bottom = pos.y+height-1;

    }
    GridRect(int left, int top, int right, int bottom) {
        
        this->x = left; this->y = top;
        this->width = right - left +1; this->height = bottom - top +1;
        this->left = left; this->top = top; this->right = right; this->bottom = bottom;
        
    }

    GridRect InsideRect() {

        int _left = (width <= 2)? left : left+1;
        int _right = (width <= 2) ? right : right - 1;
        int _top = (height <= 2) ? top : top + 1;
        int _bottom = (height <= 2) ? bottom : bottom - 1;

        return GridRect(_left, _top, _right, _bottom);

    }
};

//そのグリッドのタイル（属性）
enum class ETileType {
    outside_wall_id,
    inside_wall_id,
    room_id,
    entrance_id,
    way_id, //通路
};

//どうデータを格納するか
enum class ETileSetType {
    ALL,
    OUTSIDE,
    INSIDE,
};

enum class DirectionType {
    direction_north,
    direction_south,
    direction_west,
    direction_east,
    direction_count,
};

typedef std::vector<std::vector<ETileType>> GridMapData;


//プロトタイプ宣言
void SetTileData(GridMapData* map_data, GridRect& rect_data, ETileType tile_type, ETileSetType set_type = ETileSetType::ALL);


//ダンジョン作成関数（フロア連結型）
//①全体の矩形を決める　幅と高さ
//②中心に部屋を作る（このとき部屋の最大値をあらかじめ決めておく）
//③つくったマスの情報を配列に格納する　
//④部屋の内壁部分から次のフロアパーツにつながる連結部分を決める（元ある部屋と重ならないように）
//⑤連結部分から次に部屋を作るか道を作るか決める
//⑥部屋または道がどの方向に伸びるか決める
//⑦部屋・道をつくる
//⑧情報を格納する
//⑨あらかじめ決めた部屋数になるまで④～⑧を繰り返す
//⑩マップの配列を返す



//ダンジョン作成関数（フロア連結型）
void CreateDungeon(GridMapData* data) {


    //①全体の矩形を決める　幅と高さ

    //もとの大きさ
    int dungeon_width = MAP_WIDTH;
    int dungeon_height = MAP_HEIGHT;

    GridRect map(Point(0, 0),dungeon_width, dungeon_height);
   //データを幅と高さでダンジョンデータを初期化
    (*data).resize(dungeon_height); 
    
    for (int i = 0; i < dungeon_height; i++) 
    { (*data)[i].resize(dungeon_width); }

    SetTileData(data, map,ETileType::outside_wall_id);

    //②中心に部屋を作る（このとき部屋の最大値をあらかじめ決めておく）
    
    //中心を求める
    int center_x = dungeon_width / 2;// 10/2=5  11/2=5.5 = 5
    int center_y = dungeon_height / 2;
    //奇数だと真ん中より1小さくなる

    //中心点
    Point center_point(center_x, center_y);
    
    //中心点から部屋作成　幅・高さ　5　外壁含め7　
    int dist = 6;
    GridRect center_rect(center_point.x - dist, center_point.y - dist, center_point.x + dist, center_point.y + dist);

    //③つくったマスの情報を配列に格納する
    //別の関数にRectを渡して格納させる
    SetTileData(data, center_rect,ETileType::room_id);
    SetTileData(data, center_rect, ETileType::inside_wall_id, ETileSetType::OUTSIDE);

    //部屋の情報を保存
    std::vector<GridRect> rect_vector;

    rect_vector.push_back(center_rect);

    //④部屋の内壁部分から次のフロアパーツにつながる連結部分を決める（元ある部屋と重ならないように）
    //決める方法
    //①つくった矩形を保存しておき　そこらか矩形を取り出す　そして矩形の周りからランダムに決める
    
    //ランダムに部屋を１つ決める
    int index = rand() % rect_vector.size();

    GridRect temp_rect = rect_vector[index].InsideRect();

    //ルール1　部屋や通路からの道は上下右左から一方向だけとする

    int x =Rand(temp_rect.left, temp_rect.right);

    int y =Rand(temp_rect.top, temp_rect.bottom);

    Point(x, y);

}

void SetTileData(GridMapData* map_data, GridRect& rect_data,ETileType tile_type,ETileSetType set_type) {

    GridRect rect = rect_data;
   
    // 配列より矩形が大きい場合 エラー表示
    assert(rect.width <= (*map_data).size()&&rect.height <= (*map_data)[0].size());

    switch (set_type)
    {
    case ETileSetType::ALL:
        
        rect = rect_data;

        //矩形全ての位置にデータを格納する
        for (int y = rect.top; y <= rect.bottom; y++)
            {
                for (int x = rect.left; x <= rect.right; x++)
                {
            
                    (*map_data)[y][x] = tile_type;

                }
            }
        break;
    case ETileSetType::OUTSIDE:

        rect = rect_data;

        //右方向にtopとbottomの位置で2回　格納
        for (int y = rect.top; y <= rect.bottom; y+=rect.height-1){
            for (int x = rect.left; x <= rect.right; x++) {
                (*map_data)[y][x] = tile_type;
            }
        }
        //縦方向にleftとrightの位置で2回　（このときyは1ずつ小さくする）
        for (int x = rect.left; x <= rect.right; x += rect.width-1) {
            for (int y = rect.top+1; y <= rect.bottom-1; y++)
            {
                (*map_data)[y][x] = tile_type;
            }
        }
        break;
    default:
        break;
    }

}


//⑤連結部分から次に部屋を作るか道を作るか決める
//⑥部屋または道がどの方向に伸びるか決める
//⑦部屋・道をつくる
//⑧情報を格納する
//⑨あらかじめ決めた部屋数になるまで④～⑧を繰り返す
//⑩マップの配列を返す

void DebugMap(const GridMapData& map) {

    int height = map[0].size();
    int width = map.size();

    for (int y = 0; y < height; y++) {
        
        for (int x = 0; x < width; x++) {
            if (x == 0) printf("\n");
            ETileType tile = map[y][x];
            switch (tile)
            {
            case ETileType::outside_wall_id: printf("・"); break;
            case ETileType::inside_wall_id: printf("■"); break;
            case ETileType::room_id: printf("☆"); break;
            case ETileType::entrance_id: printf("□"); break;
            case ETileType::way_id: printf("＊"); break;
            default:
                break;
            }

        }
    }

}

void main() {

    //ダンジョン作成関数

    GridMapData map_data;

    CreateDungeon(&map_data);

    DebugMap(map_data);



}