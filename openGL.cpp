// openGL.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。


// OpenGLで円の描画
#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <math.h>
#define M_PI 3.141592 // 円周率
#define PART 100 // 分割数

static GLfloat ang = 0.0;


void display(void)
{
    int i, n = PART;
    float x, y, r = 0.5;
    double rate;
    glClear(GL_COLOR_BUFFER_BIT); // ウィンドウの背景をglClearColor()で指定された色で塗りつぶす
    glColor3f(1.0, 1.0, 0.0); // 描画物体に白色を設定

    glPushMatrix();
    glRotatef(ang, 0.0, 0.0, 1.0);
    //    glRectf( -12.0, -15.0, 15.0, 15.0 );

    glBegin(GL_POLYGON); // ポリゴンの描画

    // 円を描画

    for (i = 0; i < n; i++) {
        // 座標を計算
        rate = (double)i / n;
        x = r * cos(2.0 * M_PI * rate);
        y = r * sin(2.0 * M_PI * rate);

        //パックマンの口の条件
        if (i < 10) {
            x = 0;
            y = 0;
        }

        if (i > 90) {
            x = 0;
            y = 0;
        }

        //--------------------------------------------------------
        //
        glVertex3f(x, y, 0.0); // 頂点座標を指定



    }
    glEnd(); // ポリゴンの描画終了
  //  glFlush();//まだ実行されていない命令をすべて実行
  //  glPopMatrix();
    glutSwapBuffers();//図形表記に必要
}

void simu(void)
{
    ang = ang + 1.0;
    if (ang > 360.0)
        ang = ang - 360.0;
    glutPostRedisplay();

}




void init(void)
{
    glClearColor(0.0, 0.0, 0.0, 0.0);

    glShadeModel(GL_FLAT);
}


void Keyboard(unsigned char key, int x, int y)
{
    if (key == 'a') {
        exit(0);
    }
    else if (key == 'b') {
        glutIdleFunc(simu);
    }
}


int main(int argc, char* argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);

    glutInitWindowPosition(250, 250);//ウィンドウの位置
    glutInitWindowSize(500, 500);//ウィンドウのサイズ

    glutCreateWindow(argv[0]);
    init();
    glutKeyboardFunc(Keyboard);
    glutDisplayFunc(display); // ディスプレイコールバック関数の指定
    glutMainLoop(); // イベント待ちループ
    return 0;
}

// プログラムの実行: Ctrl + F5 または [デバッグ] > [デバッグなしで開始] メニュー
// プログラムのデバッグ: F5 または [デバッグ] > [デバッグの開始] メニュー

// 作業を開始するためのヒント: 
//    1. ソリューション エクスプローラー ウィンドウを使用してファイルを追加/管理します 
//   2. チーム エクスプローラー ウィンドウを使用してソース管理に接続します
//   3. 出力ウィンドウを使用して、ビルド出力とその他のメッセージを表示します
//   4. エラー一覧ウィンドウを使用してエラーを表示します
//   5. [プロジェクト] > [新しい項目の追加] と移動して新しいコード ファイルを作成するか、[プロジェクト] > [既存の項目の追加] と移動して既存のコード ファイルをプロジェクトに追加します
//   6. 後ほどこのプロジェクトを再び開く場合、[ファイル] > [開く] > [プロジェクト] と移動して .sln ファイルを選択します
