/*
 * バンダイナムコスタジオ 2021年度 放課後インターン プログラム能力選考問題
 */

#include <iostream>
#include <stdio.h>
 /*
  * 対応表
  * 暗号化仕様書からコピペするのは面倒なので用意しておきました。
  */
constexpr char table[] =
{
    'a','b','c','d','e','f','g','h',
    'i','j','k','l','m','n','o','p',
    'q','r','s','t','u','v','w','x',
    'y','z','7','6','5','4','3','2'
};

/**
 * @brief 暗号化関数
 * @param input_size 入力データのサイズ(単位はByte)です。この問題では必ず 0 ～ 32 の値が入力されます。
 * @param input_data 入力データ(バイナリデータ)です。
 * @param output_string 出力データです。ヌル終端文字列（ASCIIZ文字列)を返してください。入力データサイズが0の場合でも、ヌル文字('\0')を返してください。
 */
void encode(const int input_size, const uint8_t* input_data, char* output_string)
{
    //注意：関数名や引数の型や数を変更するとビルドに通らなくなりますよ。

    //TODO: 暗号化仕様書に基づき、この関数を実装してください
    // デバッグ用に標準出力を使用していただいて問題ありません。
    // std::cout << "test" << std::endl;
    std::cout << input_size << std::endl;
    //もしサイズが0なら
    if (input_size <= 0) {
        output_string[0] = '\0';
        std::cout << "0です" << std::endl;
        return;
    }

    //データを移しておく
    uint8_t temp;
    printf("%u\n", *input_data);
    //バイト数をビットに直し５で割った余りを求める
    int i = (input_size * 8) % 5;

    //5つずつわける区分の数
    int n;
    //余りが0ではないのなら
    if (i != 0) {
        //0を入れる数を求める
        int s = 5 - i;

        std::cout << s << std::endl;

        std::cout << (*input_data) << std::endl;
        //その数だけdataを左にシフトする
        temp = (*input_data) << s;

        std::cout << temp << std::endl;

        //割った数+1が文字数
        n = (input_size * 8) / 5 + 1;

        std::cout << n << std::endl;
    }
    else {

        //0なら割った数が文字数
        n = (input_size * 8) / 5;

        std::cout << n << std::endl;
    }


    uint8_t top;
    //文字を格納する
    //５つずつ格納し
    for (int i = 0; i < n; i++) {

        //論理積とるための変数
        uint8_t over = 0b11111;

        //std::cout << "オーバー" << over << std::endl;
        printf("%u\n", over);
        //論理シフトとする
        over = over << ((n - 1) * 5);

        std::cout << "オーバー2" << over << std::endl;
        printf("%u\n", over);
        //データから論理し先頭だけを取り出す
        top = temp & over;

        std::cout << "トップ" << top << std::endl;
        //先頭だけのものを取り出し右にシフトし戻す
        top = top >> ((n - 1) * 5);

        std::cout << "トップ2" << top << std::endl;
        //文字を格納する
        output_string[i] = table[top];
        //データをずらす
        temp = temp << 5;
    }

    //最後に\0を入れる
    output_string[n] = '\0';

}
