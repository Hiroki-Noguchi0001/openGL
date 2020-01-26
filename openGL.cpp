
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
    glColor3f(0.0, 0.0, 0.0); // 描画物体に白色を設定

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

void resize(int w, int h) {
    glViewport(0, 0, w, h); // ウィンドウ全体をビューポートにする
    glLoadIdentity(); // 変換行列の初期化
    // スクリーン上の表示域をビューポートの大きさに比例させる
    glOrtho(-w / 400.0, w / 400.0, -h / 400.0, h / 400.0, -1.0, 1.0);
}


void init(void)
{
    glClearColor(1.0, 1.0, 1.0, 0.0);

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
    glutInit(&argc, argv);// GLUT 及び OpenGL 環境を初期化する
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    // ディスプレーの表示モードを設定する
    // RGB (赤緑青, 光の三原色)
    glutInitWindowPosition(200, 200);//ウィンドウの位置
    glutInitWindowSize(500, 500);//ウィンドウのサイズ
    glutCreateWindow(argv[0]);
    glutReshapeFunc(resize);
    init();
    glutKeyboardFunc(Keyboard);
    glutDisplayFunc(display); // ディスプレイコールバック関数の指定
    glutMainLoop(); // イベント待ちループ
    return 0;
}
