// OpenGLで円の描画
#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <math.h>
#define M_PI 3.141592 // 円周率
#define PART 100 // 分割数

static GLfloat ang = 0.0;

static GLfloat widthzero = 0;
static GLfloat heightzero = 0;
static GLfloat width = 100.0;
static GLfloat height = 100.0;

struct BBB {
    double r;
    double x;
    double y;
};
BBB ball;


void packman(double r)
{
    int i, n = PART;
    double x, y= 0.5;
    double rate;
    glBegin(GL_POLYGON); // ポリゴンの描画
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
        glVertex2d(x, y); // 頂点座標を指定
    }
    glEnd(); // ポリゴンの描画終了
}

void display(void)
{

    glClear(GL_COLOR_BUFFER_BIT); // ウィンドウの背景をglClearColor()で指定された色で塗りつぶす

    glColor3f(1.0, 0.0, 0.0); // 描画物体に白色を設定
   
    glPushMatrix();
 
    glTranslatef(ball.x, ball.y, 0.0);//移動
    glRotatef(ang, 0.0, 0.0, 1.0);//回転

    packman(ball.r);//パックマン描画
    glutSwapBuffers();//図形表記に必要

    glPopMatrix();
}

void simu(void)
{
    ang = ang + 1.0;
    ball.y = ball.y - 1.0;
    
    if ((ball.y + ball.r) <= width) {
        ball.y = ball.y + 50.0;
    }
    /*
    if ((ball.y + ball.r) >= width2) {
        ball.y = ball.y - 1.0;
    }
    */

    glutPostRedisplay();

}

void reshape(int w,int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(widthzero, width, heightzero, height, -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void init(void)
{
    glClearColor(1.0, 1.0, 1.0, 0.0);

    glShadeModel(GL_FLAT);
}


void Keyboard(unsigned char key, int x, int y)
{
    if (key == '\033' /* '\033' は ESC の ASCII コード */) {
        exit(0);
    }
    else if (key == 'b') {
        glutIdleFunc(simu);
    }
}


int main(int argc, char* argv[]){

    ball.r = 5;
    ball.x = 50;
    ball.y = 50;

    glutInit(&argc, argv);// GLUT 及び OpenGL 環境を初期化する
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    // ディスプレーの表示モードを設定する
    // RGB (赤緑青, 光の三原色)
    glutInitWindowPosition(200, 100);//ウィンドウの位置
    glutInitWindowSize(500, 500);//ウィンドウのサイズ
    glutCreateWindow(argv[0]);
    glutReshapeFunc(reshape);
    init();
    glutKeyboardFunc(Keyboard);
    glutDisplayFunc(display); // ディスプレイコールバック関数の指定
    glutMainLoop(); // イベント待ちループ
    return 0;
}
