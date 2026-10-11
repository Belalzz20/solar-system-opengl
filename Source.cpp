#include <GL/glut.h>
#include <cmath>
#include <vector>
#include <cstdlib>



struct Body {
    const char* name;
    float orbitR;
    float radius;
    float orbitSpd;
    float spinSpd;
    float r, g, b;
    bool ring;
    float ringIn, ringOut;
};

struct V3 { float x, y, z; };



static int W = 900, H = 700;


static float camDist = 55.0f;
static float camYaw = 45.0f;
static float camPitch = 30.0f;

static float starsAngle = 0.0f;


static std::vector<Body> bodies;
static std::vector<float> orbitA;
static std::vector<float> spinA;
static std::vector<V3> ringPts;
static std::vector<V3> stars;



static float rad(float d) { return d * 3.1415926535f / 180.f; }

static void build();
static void buildStars();   
static void init();



static void build()
{
    bodies = {
        {"Mercury",  5.0f, 0.30f, 2.8f, 6.0f, 0.7f, 0.7f, 0.7f, false, 0,0},
        {"Venus",    7.0f, 0.90f, 2.2f, 5.0f, 0.95f,0.8f, 0.4f, false, 0,0},
        {"Earth",    9.5f, 1.00f, 1.9f, 7.0f, 0.2f, 0.5f, 1.0f, false, 0,0},
        {"Mars",    12.0f, 0.50f, 1.6f, 6.0f, 0.9f, 0.3f, 0.2f, false, 0,0},
        {"Jupiter", 16.0f, 3.00f, 1.1f, 9.0f, 0.9f, 0.7f, 0.5f, false, 0,0},
        {"Saturn",  22.0f, 2.00f, 0.9f, 8.0f, 0.9f, 0.85f,0.6f, true,  3.2f, 5.2f},
        {"Uranus",  28.0f, 1.50f, 0.7f, 7.0f, 0.6f, 0.9f, 0.9f, false, 0,0},
        {"Neptune", 33.0f, 1.40f, 0.6f, 7.0f, 0.2f, 0.3f, 0.9f, false, 0,0}
    };

    orbitA.assign(bodies.size(), 0.f);
    spinA.assign(bodies.size(), 0.f);

    ringPts.clear();
    const int N = 2500;
    for (const auto& b : bodies) {
        if (!b.ring) continue;
        ringPts.reserve(N);
        for (int i = 0; i < N; i++) {
            float t = (float)rand() / RAND_MAX;
            float rr = b.ringIn + t * (b.ringOut - b.ringIn);
            float a = ((float)rand() / RAND_MAX) * 2.f * 3.1415926535f;
            ringPts.push_back({ rr * std::cos(a), 0.f, rr * std::sin(a) });
        }
    }
}

static void init()
{
    glClearColor(0.f, 0.f, 0.f, 1.f);
    glEnable(GL_DEPTH_TEST);

    build();
    buildStars();  
}




static void camera()
{
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    float y = rad(camYaw);
    float p = rad(camPitch);

    float x = camDist * std::cos(p) * std::sin(y);
    float yy = camDist * std::sin(p);
    float z = camDist * std::cos(p) * std::cos(y);

    gluLookAt(x, yy, z, 0, 0, 0, 0, 1, 0);
}



static void drawOrbit(float r)
{
    glBegin(GL_LINE_LOOP);
    glColor3f(0.25f, 0.25f, 0.25f);
    for (int i = 0; i < 120; i++) {
        float a = i * 2.f * 3.1415926535f / 120.f;
        glVertex3f(r * std::cos(a), 0.f, r * std::sin(a));
    }
    glEnd();
}

static void drawStars()
{
    glPushMatrix();
    glRotatef(starsAngle, 0.f, 1.f, 0.f);

    glDisable(GL_LIGHTING);
    glBegin(GL_POINTS);

    for (size_t i = 0; i < stars.size(); i++)
    {
        float brightness = 0.6f + (i % 10) * 0.04f;
        glColor3f(brightness, brightness, brightness);
        glVertex3f(stars[i].x, stars[i].y, stars[i].z);
    }

    glEnd();
    glPopMatrix();
}



static void sun()
{
    glColor3f(1.f, 1.f, 0.f);
    glutSolidSphere(3.2, 40, 40); 
}

static void ring()
{
    glPointSize(2.f);
    glBegin(GL_POINTS);
    glColor3f(0.9f, 0.9f, 0.7f);
    for (const auto& p : ringPts) glVertex3f(p.x, p.y, p.z);
    glEnd();
}

static void planet(size_t i)
{
    const Body& b = bodies[i];
    glPushMatrix();

 
    float tiltY = (float)i * 0.12f;

    glRotatef(orbitA[i], 0, 1, 0);
    glTranslatef(b.orbitR, tiltY, 0);
    glRotatef(spinA[i], 0, 1, 0);

    glColor3f(b.r, b.g, b.b);
    glutSolidSphere(b.radius, 30, 30);

    if (b.ring) ring();
    glPopMatrix();
}



static void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, (double)W / H, 0.1, 300.0);

    camera();

    drawStars();   

    sun();
    for (const auto& b : bodies) drawOrbit(b.orbitR);
    for (size_t i = 0; i < bodies.size(); i++) planet(i);

    glutSwapBuffers();
}


static void tick(int)
{
    for (size_t i = 0; i < bodies.size(); i++) {
        orbitA[i] += bodies[i].orbitSpd;
        spinA[i] += bodies[i].spinSpd;

        if (orbitA[i] >= 360.f) orbitA[i] -= 360.f;
        if (spinA[i] >= 360.f) spinA[i] -= 360.f;
    }

   
    starsAngle += 0.02f;
    if (starsAngle >= 360.f) starsAngle -= 360.f;

    glutPostRedisplay();
    glutTimerFunc(16, tick, 0);
}


static void reshape(int w, int h)
{
    W = (w < 1) ? 1 : w; H = (h < 1) ? 1 : h;
    glViewport(0, 0, W, H);
}

static void buildStars()
{
    stars.clear();
    const int STAR_COUNT = 5000;
    const float STAR_RADIUS = 220.0f;

    for (int i = 0; i < STAR_COUNT; i++)
    {
        float theta = ((float)rand() / RAND_MAX) * 2.0f * 3.1415926535f;
        float phi = ((float)rand() / RAND_MAX) * 3.1415926535f;

        V3 s;
        s.x = STAR_RADIUS * std::sin(phi) * std::cos(theta);
        s.y = STAR_RADIUS * std::cos(phi);
        s.z = STAR_RADIUS * std::sin(phi) * std::sin(theta);

        stars.push_back(s);
    }
}


static void keys(unsigned char k, int, int)
{
    if (k == 27) std::exit(0);
    if (k == '+') camDist -= 2.f;
    if (k == '-') camDist += 2.f;
    if (k == 'a') camYaw -= 4.f;
    if (k == 'd') camYaw += 4.f;
    if (k == 'w') camPitch += 3.f;
    if (k == 's') camPitch -= 3.f;
    glutPostRedisplay();
}



int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(W, H);
    glutCreateWindow("CS-4270 - Solar System");

    init();

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keys);
    glutTimerFunc(16, tick, 0);

    glutMainLoop();
    return 0;
}
