/*
 * �o���_�C�i���R�X�^�W�I 2021�N�x ���ی�C���^�[�� �v���O�����\�͑I�l���
 */

#include <iostream>
#include <stdio.h>
 /*
  * �Ή��\
  * �Í����d�l������R�s�y����͖̂ʓ|�Ȃ̂ŗp�ӂ��Ă����܂����B
  */
constexpr char table[] =
{
    'a','b','c','d','e','f','g','h',
    'i','j','k','l','m','n','o','p',
    'q','r','s','t','u','v','w','x',
    'y','z','7','6','5','4','3','2'
};

/**
 * @brief �Í����֐�
 * @param input_size ���̓f�[�^�̃T�C�Y(�P�ʂ�Byte)�ł��B���̖��ł͕K�� 0 �` 32 �̒l�����͂���܂��B
 * @param input_data ���̓f�[�^(�o�C�i���f�[�^)�ł��B
 * @param output_string �o�̓f�[�^�ł��B�k���I�[������iASCIIZ������)��Ԃ��Ă��������B���̓f�[�^�T�C�Y��0�̏ꍇ�ł��A�k������('\0')��Ԃ��Ă��������B
 */
void encode(const int input_size, const uint8_t* input_data, char* output_string)
{
    //���ӁF�֐���������̌^�␔��ύX����ƃr���h�ɒʂ�Ȃ��Ȃ�܂���B

    //TODO: �Í����d�l���Ɋ�Â��A���̊֐����������Ă�������
    // �f�o�b�O�p�ɕW���o�͂��g�p���Ă��������Ė�肠��܂���B
    // std::cout << "test" << std::endl;
    std::cout << input_size << std::endl;
    //�����T�C�Y��0�Ȃ�
    if (input_size <= 0) {
        output_string[0] = '\0';
        std::cout << "0�ł�" << std::endl;
        return;
    }

    //�f�[�^���ڂ��Ă���
    uint8_t temp;
    printf("%u\n", *input_data);
    //�o�C�g�����r�b�g�ɒ����T�Ŋ������]������߂�
    int i = (input_size * 8) % 5;

    //5���킯��敪�̐�
    int n;
    //�]�肪0�ł͂Ȃ��̂Ȃ�
    if (i != 0) {
        //0�����鐔�����߂�
        int s = 5 - i;

        std::cout << s << std::endl;

        std::cout << (*input_data) << std::endl;
        //���̐�����data�����ɃV�t�g����
        temp = (*input_data) << s;

        std::cout << temp << std::endl;

        //��������+1��������
        n = (input_size * 8) / 5 + 1;

        std::cout << n << std::endl;
    }
    else {

        //0�Ȃ犄��������������
        n = (input_size * 8) / 5;

        std::cout << n << std::endl;
    }


    uint8_t top;
    //�������i�[����
    //�T���i�[��
    for (int i = 0; i < n; i++) {

        //�_���ςƂ邽�߂̕ϐ�
        uint8_t over = 0b11111;

        //std::cout << "�I�[�o�[" << over << std::endl;
        printf("%u\n", over);
        //�_���V�t�g�Ƃ���
        over = over << ((n - 1) * 5);

        std::cout << "�I�[�o�[2" << over << std::endl;
        printf("%u\n", over);
        //�f�[�^����_�����擪���������o��
        top = temp & over;

        std::cout << "�g�b�v" << top << std::endl;
        //�擪�����̂��̂����o���E�ɃV�t�g���߂�
        top = top >> ((n - 1) * 5);

        std::cout << "�g�b�v2" << top << std::endl;
        //�������i�[����
        output_string[i] = table[top];
        //�f�[�^�����炷
        temp = temp << 5;
    }

    //�Ō��\0������
    output_string[n] = '\0';

}
