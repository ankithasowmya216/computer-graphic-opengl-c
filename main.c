#include "bibutil.h"
#include <stdio.h>
#include <stdlib.h>
#include <GL/freeglut.h>

//#define DEBUG 1
// Variáveis para controles de navegação
GLfloat angle, fAspect;
GLfloat rotX, rotY, rotX_ini, rotY_ini;
GLfloat obsX, obsY, obsZ, obsX_ini, obsY_ini, obsZ_ini;
int x_ini,y_ini,bot;

int rotacionado = 0, naEstrada = 0, loop = 1;

GLfloat cX = 0, cY = 0, cZ = 0, cR = 0;

// Apontador para objeto
OBJ *casa;
OBJ *carro;
OBJ *balanco;
OBJ *arvore;
OBJ *hidrante;

void IluminacaoAmbiente() {

	GLfloat luzAmbiente[4]={0.4, 0.4, 0.4, 0.0};
	GLfloat luzDifusa[4]={0.8, 0.8, 0.8, 0.0};
	GLfloat luzEspecular[4]={0.6, 0.6, 0.6, 0.0};
	GLfloat posicaoLuz[4]={0.0, 10.0, 100.0, 1.0};


	// Define os parâmetros da luz de número 0
	glLightfv(GL_LIGHT0, GL_AMBIENT, luzAmbiente);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, luzDifusa );
	glLightfv(GL_LIGHT0, GL_SPECULAR, luzEspecular );
	glLightfv(GL_LIGHT0, GL_POSITION, posicaoLuz );

	// Ativa o uso da luz ambiente
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, luzAmbiente);
}

void IluminacaoLocal() {

	GLfloat white[4]={1.0, 1.0, 0.0, 1.0};
	GLfloat posicaoLuz[4]={-370.0, 450.0, -3000.0, 1.0};


	// Define os parâmetros da luz de número 0
	glLightfv(GL_LIGHT1, GL_AMBIENT, white);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, white);
	glLightfv(GL_LIGHT1, GL_SPECULAR, white);
	glLightfv(GL_LIGHT1, GL_POSITION, posicaoLuz );
	
	//ativa a atenuação
	glLightf(GL_LIGHT1, GL_CONSTANT_ATTENUATION, 0.9f);    //define a0
	glLightf(GL_LIGHT1, GL_LINEAR_ATTENUATION, 0.9f) ;     //define a1
	glLightf(GL_LIGHT1, GL_QUADRATIC_ATTENUATION, 0.9f) ;  //define a2

}

void DesenhaCasa(void) {
	// Capacidade de brilho do material
	GLfloat especularidade[4]={1.0,1.0,1.0,1.0};
	GLint especMaterial = 60;

	// Define a refletância do material
	glMaterialfv(GL_FRONT,GL_SPECULAR, especularidade);
	// Define a concentração do brilho
	glMateriali(GL_FRONT,GL_SHININESS,especMaterial);

	glColor3f(0.361f, 0.251f, 0.2f);

	glPushMatrix();
    glRotatef(rotX,1,0,0);
	glRotatef(rotY,0,1,0);
	glTranslated(-230, 172, -185);

	DesenhaObjeto(casa);

    glPopMatrix();
}

void DesenhaCarro(void) {

	// Capacidade de brilho do material
	GLfloat especularidade[4]={1.0,1.0,1.0,1.0};
	GLint especMaterial = 120;

	// Define a refletância do material
	glMaterialfv(GL_FRONT,GL_SPECULAR, especularidade);
	// Define a concentração do brilho
	glMateriali(GL_FRONT,GL_SHININESS,especMaterial);

	glColor3f(0.137f, 0.137f, 0.557f);

	glPushMatrix();
    glRotatef(rotX,1,0,0);
	glRotatef(rotY,0,1,0);

	glTranslated(cX, cY, cZ);
	glRotatef(cR,0,1,0);

	DesenhaObjeto(carro);

    glPopMatrix();
}

void DesenhaGrama(void) {

    glPushMatrix();

    glRotatef(rotX,1,0,0);
    glRotatef(rotY,0,1,0);

    glTranslatef(0, -71, 0);
    glScalef(1000, 0, -1000);

    glColor3f(0, 0.39f, 0);

    //textura
    glutSolidCube(100);

    glPopMatrix();
}

void DesenhaBalanco(void) {

	// Capacidade de brilho do material
	GLfloat especularidade[4]={1.0,1.0,1.0,1.0};
	GLint especMaterial = 60;

	// Define a refletância do material
	glMaterialfv(GL_FRONT,GL_SPECULAR, especularidade);
	// Define a concentração do brilho
	glMateriali(GL_FRONT,GL_SHININESS,especMaterial);
	
	glColor3f(1.0f, 1.0f, 0.0f);

	glPushMatrix();
    glRotatef(rotX,1,0,0);
	glRotatef(rotY,0,1,0);
	glTranslated(-260, -25, 20);
    glScalef(8, 8, 8);

	DesenhaObjeto(balanco);

    glPopMatrix();
}

void DesenhaArvore(void) {

	// Capacidade de brilho do material
	GLfloat especularidade[4]={1.0,1.0,1.0,1.0};
	GLint especMaterial = 10;

	// Define a refletância do material
	glMaterialfv(GL_FRONT,GL_SPECULAR, especularidade);
	// Define a concentração do brilho
	glMateriali(GL_FRONT,GL_SHININESS,especMaterial);
	
	glColor3f(1.0f, 0.647f, 0.0f);

	glPushMatrix();
    glRotatef(rotX,1,0,0);
	glRotatef(rotY,0,1,0);
	glTranslated(0, 300, -800);
    glScalef(40, 40, 40);

	DesenhaObjeto(arvore);

    glPopMatrix();
}

void DesenhaHidrante(void) {

	// Capacidade de brilho do material
	GLfloat especularidade[4]={1.0,1.0,1.0,1.0};
	GLint especMaterial = 100;

	// Define a refletância do material
	glMaterialfv(GL_FRONT,GL_SPECULAR, especularidade);
	// Define a concentração do brilho
	glMateriali(GL_FRONT,GL_SHININESS,especMaterial);
	
	glColor3f(1.0f, 0.0f, 0.0f);

	glPushMatrix();
    glRotatef(rotX,1,0,0);
	glRotatef(rotY,0,1,0);
	glTranslated(-230, -70, 700);
    glScalef(80, 80, 80);

	DesenhaObjeto(hidrante);

    glPopMatrix();
}

// Função callback de redesenho da janela de visualização
void Desenha(void) {
	// Limpa a janela de visualização com a cor
	// de fundo definida previamente
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);

	IluminacaoAmbiente();
	IluminacaoLocal();

	DesenhaCasa();
	DesenhaCarro();
	DesenhaGrama();
	DesenhaBalanco();
	DesenhaArvore();
	DesenhaHidrante();

	// Executa os comandos OpenGL
	glutSwapBuffers();
}

void Animacao() {
	if (naEstrada == 0) {
		if (cZ < 750) {
			cZ += 10;
		} else if (cR < 90){
			rotacionado = 1;
			cR += 10;
			cX += 15;
			cZ += 10;
		} else {
			cX -= 10;
			if (cX <= -2000) {
				cX = 2000;
			}
			if (cX == 150) {
				naEstrada = 1;
			}
		}
	} else {
		if ((cZ > 0) && (rotacionado == 0)) {
			cZ -= 10;
		} else if (cR > 0) {
			cR -= 10;
			cX -= 15;
			cZ -= 10;
			if (cR == 0) rotacionado = 0;
		} else if (cZ == 0) {
			naEstrada = 0;
			loop = 0;
		}
	}
}

// Função usada para especificar a posição do observador virtual
void PosicionaObservador(void) {
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();//carrega a matriz de identidade
    if (rotX < 0) {
    	rotX = 0;
    } else if (rotX > 60) {
    	rotX = 60;
    }
    if (rotY < -90) {
    	rotY = -90;
    } else if (rotY > 90) {
    	rotY = 90;
    }
    gluLookAt(obsX,obsY,obsZ,	//posição da câmera
              0.0,0.0,0.0,  	//para onde a câmera aponta
              0.0,1.0,0.0);		//vetor view-up//
}

// Função usada para especificar o volume de visualização
void EspecificaParametrosVisualizacao(void) {

	// Especifica sistema de coordenadas de projeção
	glMatrixMode(GL_PROJECTION);
	// Inicializa sistema de coordenadas de projeção
	glLoadIdentity();

	// Especifica a projeção perspectiva(angulo,aspecto,dnear,dfar)
	gluPerspective(angle,fAspect,0.01,4000);

	// Chama as funções que especificam os parâmetros da câmera e os parâmetros de iluminação
	PosicionaObservador();
}

// Função callback chamada quando o tamanho da janela é alterado
void AlteraTamanhoJanela(GLsizei w, GLsizei h) {
	// Para previnir uma divisão por zero
	if ( h == 0 ) h = 1;

	// Especifica as dimensões da viewport
	glViewport(0, 0, w, h);

	// Calcula a correção de aspecto
	fAspect = (GLfloat)w/(GLfloat)h;

	EspecificaParametrosVisualizacao();
}

// Função callback chamada para gerenciar eventos de teclas normais (ESC)
void Teclas (unsigned char tecla, int x, int y) {
	if(tecla==27) // ESC ?
	{
		// Libera memória e finaliza programa
		LiberaObjeto(casa);
		LiberaObjeto(carro);
		LiberaObjeto(balanco);
		LiberaObjeto(arvore);
		LiberaObjeto(hidrante);
		exit(0);
	}
	if(tecla=='l')
	{
		if(glIsEnabled(GL_LIGHTING))
			glDisable(GL_LIGHTING);
		else
            glEnable(GL_LIGHTING);
	}
	glutPostRedisplay();
}

// Função callback para tratar eventos de teclas especiais
void TeclasEspeciais (int tecla, int x, int y) {
	switch (tecla)
	{
		case GLUT_KEY_HOME:	if(angle>=30)  angle -=5;
							break;
		case GLUT_KEY_END:	if(angle<=100) angle +=5;
							break;
		case GLUT_KEY_LEFT:	Animacao();
							break;
	}
	EspecificaParametrosVisualizacao();
	glutPostRedisplay();
}

// Função callback para eventos de botões do mouse
void GerenciaMouse(int button, int state, int x, int y) {
	if(state==GLUT_DOWN) {
		// Salva os parâmetros atuais
		x_ini = x;
		y_ini = y;
		obsX_ini = obsX;
		obsY_ini = obsY;
		obsZ_ini = obsZ;
		rotX_ini = rotX;
		rotY_ini = rotY;
		bot = button;
	}
	else bot = -1;
}

// Função callback para eventos de movimento do mouse
#define SENS_ROT	5.0
#define SENS_OBS	15.0
#define SENS_TRANSL	20.0

void GerenciaMovim(int x, int y) {
	// Botão esquerdo
	if(bot==GLUT_LEFT_BUTTON)
	{
		// Calcula diferenças
		int deltax = x_ini - x;
		int deltay = y_ini - y;
		// E modifica ângulos
		rotY = rotY_ini - deltax/SENS_ROT;
		rotX = rotX_ini - deltay/SENS_ROT;
	}
	// Botão direito (zoom-in e zoom-out)
	else if(bot==GLUT_RIGHT_BUTTON){
		// Calcula diferença
		int deltaz = y_ini - y;
		// E modifica distância do observador
		obsZ = obsZ_ini + deltaz/SENS_OBS;
	}
	// Botão do meio
	else if(bot==GLUT_MIDDLE_BUTTON)
	{
		// Calcula diferenças
		int deltax = x_ini - x;
		int deltay = y_ini - y;
		// E modifica posições
		obsX = obsX_ini + deltax/SENS_TRANSL;
		obsY = obsY_ini - deltay/SENS_TRANSL;
	}
	PosicionaObservador();
	glutPostRedisplay();
}

void CarregarCasa(void) {
	
	casa = CarregaObjeto("house.obj", true);
    printf("Objeto carregado!");

	// E calcula o vetor normal em cada face
	if(casa->normais) {
		// Se já existirem normais no arquivo, apaga elas
		free(casa->normais);
		casa->normais_por_vertice = false;
	}
	CalculaNormaisPorFace(casa);
}

void CarregarCarro(void) {
	
	carro = CarregaObjeto("Small car.obj", true);
    printf("Objeto carregado!");

	// E calcula o vetor normal em cada face
	if(carro->normais) {
		// Se já existirem normais no arquivo, apaga elas
		free(carro->normais);
		carro->normais_por_vertice = false;
	}
	CalculaNormaisPorFace(carro);
}

void CarregarBalanco(void) {
	
	balanco = CarregaObjeto("swing.obj", true);
    printf("Objeto carregado!");

	// E calcula o vetor normal em cada face
	if(balanco->normais) {
		// Se já existirem normais no arquivo, apaga elas
		free(balanco->normais);
		balanco->normais_por_vertice = false;
	}
	CalculaNormaisPorFace(balanco);
}

void CarregarArvore(void) {
	
	arvore = CarregaObjeto("tree.obj", true);
    printf("Objeto carregado!");

	// E calcula o vetor normal em cada face
	if(arvore->normais) {
		// Se já existirem normais no arquivo, apaga elas
		free(arvore->normais);
		arvore->normais_por_vertice = false;
	}
	CalculaNormaisPorFace(arvore);
}

void CarregarHidrante(void) {
	
	hidrante = CarregaObjeto("low.obj", true);
    printf("Objeto carregado!");

	// E calcula o vetor normal em cada face
	if(hidrante->normais) {
		// Se já existirem normais no arquivo, apaga elas
		free(hidrante->normais);
		hidrante->normais_por_vertice = false;
	}
	CalculaNormaisPorFace(hidrante);
}

// Função responsável por inicializar parâmetros e variáveis
void Inicializa (void) {
	char nomeArquivo[30];

	// Define a cor de fundo da janela de visualização como branca
	glClearColor(0.53f, 0.81f, 0.93f, 1.0f);

	// Habilita a definição da cor do material a partir da cor corrente
	glEnable(GL_COLOR_MATERIAL);

	//Habilita o uso de iluminação
	glEnable(GL_LIGHTING);

	// Habilita a luz de número 0
	glEnable(GL_LIGHT0);

	// Habilita a luz de número 1
	glEnable(GL_LIGHT1);

	// Habilita o depth-buffering
	glEnable(GL_DEPTH_TEST);

	// Habilita o modelo de tonalização de Gouraud
	glShadeModel(GL_SMOOTH);

	// Inicializa a variável que especifica o ângulo da projeção
	// perspectiva
	angle=55;

	// Inicializa as variáveis usadas para alterar a posição do
	// observador virtual
	obsX = 20;
	obsY = 0;
	obsZ = 1300;

	//Carregar Objetos
	CarregarCasa();
	CarregarCarro();
	CarregarBalanco();
	CarregarArvore();
	CarregarHidrante();
}

// Programa Principal
int main(int argc, char *argv[]) {
    glutInit(&argc, argv);
	// Define do modo de operação da GLUT
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

    // Especifica a posição inicial da janela GLUT
    glutInitWindowPosition(190,50);

    // Especifica o tamanho inicial em pixels da janela GLUT
    glutInitWindowSize(910,650);

	// Cria a janela passando como argumento o título da mesma
	glutCreateWindow("-- Projeto Computacao Grafica --");

	// Registra a função callback de redesenho da janela de visualização
	glutDisplayFunc(Desenha);

	// Registra a função callback de redimensionamento da janela de visualização
	glutReshapeFunc(AlteraTamanhoJanela);

	// Registra a função callback para tratamento das teclas normais
	glutKeyboardFunc (Teclas);

	// Registra a função callback para tratamento das teclas especiais
	glutSpecialFunc (TeclasEspeciais);

	// Registra a função callback para eventos de botões do mouse
	glutMouseFunc(GerenciaMouse);

	// Registra a função callback para eventos de movimento do mouse
	glutMotionFunc(GerenciaMovim);

	// Chama a função responsável por fazer as inicializações
	Inicializa();

	// Inicia o processamento e aguarda interações do usuário
	glutMainLoop();

	return 0;
}
