// OpenGLで円の描画
#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <math.h>
#define M_PI 3.141592 // 円周率
#define PART 100 // 分割数
#define G 9.8//重力加速度
#define dt 0.01//時間
#define bound 0.87//反発係数

static GLfloat ang = 0.0;
static GLfloat widthzero = 0;
static GLfloat heightzero = 0;
static GLfloat width = 200.0;
static GLfloat height = 200.0;

struct BALL {
    double r;//円の半径
    double x;//xの座標
    double y;//yの座標
    double vx;//xの速度
    double vy;//yの速度
    double ax;//xの加速度
    double ay;//yの加速度
};
BALL ball;

void foot() {
    glBegin(GL_POLYGON);
    glVertex2d(50, 100);
    glVertex2d(50, 50);
    glVertex2d(60, 50);
    glVertex2d(60, 100);
    glEnd();
    glFlush();

    glBegin(GL_POLYGON);
    glVertex2d(60, 60);
    glVertex2d(60, 50);
    glVertex2d(70, 50);
    glVertex2d(70, 60);
    glEnd();
    glFlush();


}


void packman(double r)
{
    int i, n = PART;
    double x, y = 0.5;
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
    glColor3f(0.0, 0.0, 0.0); // 描画物体に白色を設定
    glPushMatrix();
    glTranslatef(ball.x, ball.y, 0.0);//移動
    glRotatef(ang, 0, 0, 1.0);//回転
    packman(ball.r);//パックマン描画
    glPopMatrix();

    glColor3f(1.0, 0.0, 1.0); // 描画物体に白色を設定
    glPushMatrix();
   // glRotatef(ang, 0, 0, 1.0);//回転
    foot();

    glPopMatrix();
    glutSwapBuffers();//図形表記に必

}

void simu(void)
{
    //回転情報
    ang = ang - 0.5;

    //速度情報
    ball.vx = ball.vx + ball.ax * dt;
    ball.vy = ball.vy + ball.ay * dt;

    //位置情報
    ball.x = ball.x + ball.vx * dt / 2.0;
    ball.y = ball.y + ball.vy * dt / 2.0;

    //衝突判定
    if ((ball.y - ball.r) <= widthzero) {
        ball.vy = ball.vy * -bound;

        ball.y = (widthzero + ball.r);

    }

    printf("X座標：%f, Y座標：%f\n", ball.x, ball.y);
    //printf("X速度：%f, Y速度：%f\n", ball.vx, ball.vy);

    glutPostRedisplay();

}

void reshape(int w, int h)
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

int main(int argc, char* argv[]) {

    ball.r = 10; //円の半径の値
    ball.x = 100;//円のｘ軸の座標の値
    ball.y = 100;//円のｙ軸の座標の値
    ball.vx = 0;//ｘの成分の速度
    ball.vy = 0;//ｙの成分の速度
    ball.ax = 0;//ｘの加速度
    ball.ay = -G;//ｙの加速度

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