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


//���_�f�[�^
struct Point {
    int x; int y;
    Point(){
        x = 0; y = 0;
    }
    Point(int x, int y) {
        this->x = x; this->y = y;
    }
};


//��`�f�[�^
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

//���̃O���b�h�̃^�C���i�����j
enum class ETileType {
    outside_wall_id,
    inside_wall_id,
    room_id,
    entrance_id,
    way_id, //�ʘH
};

//�ǂ��f�[�^���i�[���邩
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


//�v���g�^�C�v�錾
void SetTileData(GridMapData* map_data, GridRect& rect_data, ETileType tile_type, ETileSetType set_type = ETileSetType::ALL);


//�_���W�����쐬�֐��i�t���A�A���^�j
//�@�S�̂̋�`�����߂�@���ƍ���
//�A���S�ɕ��������i���̂Ƃ������̍ő�l�����炩���ߌ��߂Ă����j
//�B�������}�X�̏���z��Ɋi�[����@
//�C�����̓��Ǖ������玟�̃t���A�p�[�c�ɂȂ���A�����������߂�i�����镔���Əd�Ȃ�Ȃ��悤�Ɂj
//�D�A���������玟�ɕ�������邩������邩���߂�
//�E�����܂��͓����ǂ̕����ɐL�т邩���߂�
//�F�����E��������
//�G�����i�[����
//�H���炩���ߌ��߂��������ɂȂ�܂ŇC�`�G���J��Ԃ�
//�I�}�b�v�̔z���Ԃ�



//�_���W�����쐬�֐��i�t���A�A���^�j
void CreateDungeon(GridMapData* data) {


    //�@�S�̂̋�`�����߂�@���ƍ���

    //���Ƃ̑傫��
    int dungeon_width = MAP_WIDTH;
    int dungeon_height = MAP_HEIGHT;

    GridRect map(Point(0, 0),dungeon_width, dungeon_height);
   //�f�[�^�𕝂ƍ����Ń_���W�����f�[�^��������
    (*data).resize(dungeon_height); 
    
    for (int i = 0; i < dungeon_height; i++) 
    { (*data)[i].resize(dungeon_width); }

    SetTileData(data, map,ETileType::outside_wall_id);

    //�A���S�ɕ��������i���̂Ƃ������̍ő�l�����炩���ߌ��߂Ă����j
    
    //���S�����߂�
    int center_x = dungeon_width / 2;// 10/2=5  11/2=5.5 = 5
    int center_y = dungeon_height / 2;
    //����Ɛ^�񒆂��1�������Ȃ�

    //���S�_
    Point center_point(center_x, center_y);
    
    //���S�_���畔���쐬�@���E�����@5�@�O�Ǌ܂�7�@
    int dist = 6;
    GridRect center_rect(center_point.x - dist, center_point.y - dist, center_point.x + dist, center_point.y + dist);

    //�B�������}�X�̏���z��Ɋi�[����
    //�ʂ̊֐���Rect��n���Ċi�[������
    SetTileData(data, center_rect,ETileType::room_id);
    SetTileData(data, center_rect, ETileType::inside_wall_id, ETileSetType::OUTSIDE);

    //�����̏���ۑ�
    std::vector<GridRect> rect_vector;

    rect_vector.push_back(center_rect);

    //�C�����̓��Ǖ������玟�̃t���A�p�[�c�ɂȂ���A�����������߂�i�����镔���Əd�Ȃ�Ȃ��悤�Ɂj
    //���߂���@
    //�@��������`��ۑ����Ă����@�����炩��`�����o���@�����ċ�`�̎��肩�烉���_���Ɍ��߂�
    
    //�����_���ɕ������P���߂�
    int index = rand() % rect_vector.size();

    GridRect temp_rect = rect_vector[index].InsideRect();

    //���[��1�@������ʘH����̓��͏㉺�E���������������Ƃ���

    int x =Rand(temp_rect.left, temp_rect.right);

    int y =Rand(temp_rect.top, temp_rect.bottom);

    Point(x, y);

}

void SetTileData(GridMapData* map_data, GridRect& rect_data,ETileType tile_type,ETileSetType set_type) {

    GridRect rect = rect_data;
   
    // �z�����`���傫���ꍇ �G���[�\��
    assert(rect.width <= (*map_data).size()&&rect.height <= (*map_data)[0].size());

    switch (set_type)
    {
    case ETileSetType::ALL:
        
        rect = rect_data;

        //��`�S�Ă̈ʒu�Ƀf�[�^���i�[����
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

        //�E������top��bottom�̈ʒu��2��@�i�[
        for (int y = rect.top; y <= rect.bottom; y+=rect.height-1){
            for (int x = rect.left; x <= rect.right; x++) {
                (*map_data)[y][x] = tile_type;
            }
        }
        //�c������left��right�̈ʒu��2��@�i���̂Ƃ�y��1������������j
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


//�D�A���������玟�ɕ�������邩������邩���߂�
//�E�����܂��͓����ǂ̕����ɐL�т邩���߂�
//�F�����E��������
//�G�����i�[����
//�H���炩���ߌ��߂��������ɂȂ�܂ŇC�`�G���J��Ԃ�
//�I�}�b�v�̔z���Ԃ�

void DebugMap(const GridMapData& map) {

    int height = map[0].size();
    int width = map.size();

    for (int y = 0; y < height; y++) {
        
        for (int x = 0; x < width; x++) {
            if (x == 0) printf("\n");
            ETileType tile = map[y][x];
            switch (tile)
            {
            case ETileType::outside_wall_id: printf("�E"); break;
            case ETileType::inside_wall_id: printf("��"); break;
            case ETileType::room_id: printf("��"); break;
            case ETileType::entrance_id: printf("��"); break;
            case ETileType::way_id: printf("��"); break;
            default:
                break;
            }

        }
    }

}

void main() {

    //�_���W�����쐬�֐�

    GridMapData map_data;

    CreateDungeon(&map_data);

    DebugMap(map_data);



}