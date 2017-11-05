#include <iostream>
#include <GL/glut.h>
#include <vector>
#include "ponto.h"
#include "mathutil.h"
#include <math.h>
#include <fstream>
#include <string>
#define PI 3.1415926535

const int WINDOW_W = 500;
const int WINDOW_H = 500;

std::vector <Ponto> pontos;
bool pontosControle = true;
bool poligonalCtrl = true;
bool pontosCurva = true;
float a = -10;
double inc = 0.01; 

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
bool circulo = false;
std::vector <Ponto> pontos2;
std::vector <Ponto> pontos3;
std::vector <Ponto> saida;
std::vector <Ponto> pontosAux;
std::vector <Ponto> pontosAux2;
bool bezier = true;
Ponto p(0,0);
Ponto p2(0,0);
Ponto p3(0,0);
Ponto p4(0,0);

 if(pontos.size() > 0) {
        glBegin(GL_LINE_STRIP);
        glColor3f(1.0f, 1.0f, 1.0f);
    
        if (pontos.size() > 1) {           	                                      
		if (bezier){
		for(int i=0; i<pontos.size()-1; i++){		
			pontos2.push_back(Ponto(pontos.at(i+1).x - pontos.at(i).x, pontos.at(i+1).y - pontos.at(i).y));			
		}	
	for (float t = 0.0; t <= 1.0; t += inc) {
        	MathUtil::bezier(pontos, t, p);
		pontosAux.push_back(Ponto(p.x, p.y));				                      
		MathUtil::bezier(pontos2, t, p2);
		pontosAux2.push_back(Ponto(p2.x, p2.y));
	}   
				 		
	    		for(int i=0; i<pontosAux2.size(); i++){	
				if(pontosAux2[i].x == 0 || pontosAux2[i].y == 0){
					circulo = true;
				}	
					if (circulo){
					GLfloat angle=0;
					int j=0	;
					GLfloat circle_points = 50;
					glBegin(GL_POLYGON);
								 // Desenha a circunferencia de raio igual ao parametro da curva
					for (j = 0; j <= circle_points; j++){
						angle = 2*PI*j/circle_points;
						glVertex2f((a*cos(angle)) + pontos[i].x , a*sin(angle) + pontos[i].y);
					}
					break;
					}
				}   
									               
		if(circulo == false){
			for(int k=0; k<pontosAux.size(); k++){	
			glVertex2f(pontosAux[k].x, pontosAux[k].y);
		}
	}
	
	glEnd();
	glFlush();
	glBegin(GL_LINE_STRIP);
	
	for(int i=0; i<pontosAux.size(); i++){
	pontos3.push_back(Ponto(pontosAux2.at(i).y, pontosAux2.at(i).x * (-1)));
	p3.x = (pontosAux[i].x + (a*(pontos3[i].x/(sqrt(((pontos3[i].x*pontos3[i].x)+(pontos3[i].y*pontos3[i].y)))))));		      
	p3.y = (pontosAux[i].y + (a*(pontos3[i].y/(sqrt(((pontos3[i].x*pontos3[i].x)+pontos3[i].y*pontos3[i].y))))));	
	saida.push_back(Ponto(p3.x, p3.y));
	}
    
	   for (float t = 0.0; t <= 1.0; t += inc) {
		   MathUtil::bezier(saida, t, p4);
		    if (circulo == false){
		     glVertex2f(p4.x, p4.y);		
		}
	   }        

	glEnd();	
        glBegin(GL_LINE_STRIP); 
        glColor3f(0.0f, 1.0f, 0.0f);       
               if(poligonalCtrl){
         	      for (auto p : pontos){
	 	             glVertex2d(p.x, p.y); //Mostra a poligonal de controle, ativada pela tecla "Z"
		}		
	}	
	
    	   
        }    
        }else {
            auto p = pontos.front();
            glVertex2d(p.x, p.y);

        }

        glEnd();
        
        if(pontosControle) {
	glPointSize(5.0f);
        glBegin(GL_POINTS);                //mostra os pontos de controle, ativada pela tecla "C"
        glColor3f(1.0f, 1.0f, 0.0f);
        for(auto p : pontos){
            glVertex2d(p.x, p.y);
	}          
	glEnd();	
	}
	
	if(pontosCurva){
	glBegin(GL_POINTS);
	glColor3f(1.0f, 1.0f, 0.0f);        //mostra os pontos da curva, ativada pela tecla "X"
 		for(auto p4 : saida){            
		    glVertex2d(p4.x,p4.y);
	}        
	glEnd();
		}
    }
   
glFlush();
}

void reshape(int w, int h)
{
    glViewport(0, 0, (GLsizei) w, (GLsizei) h);
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0f, WINDOW_W, WINDOW_H, 0.0f, -5.0, 5.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void handleKeypress(unsigned char key, int x, int y)
{
    switch (key) {
    	case 'z':
    		poligonalCtrl = !poligonalCtrl;
    		break;
    	case 'x':
    		pontosCurva = !pontosCurva;
    		break;
    	case 'c' :
    		pontosControle = !pontosControle;
    		break;
        case 27: // ESC
           exit(0);
	case '+': // + 
	  if(a > -80) a = a - 5;
		break;
	case '-': // 
	  if(a < 0) a = a + 5;	     		
		break;
	
	}
    
    glutPostRedisplay();
}

void handleMouseClick(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON)
        if (state == GLUT_DOWN)
            pontos.push_back(Ponto(x, y));
    
    glutPostRedisplay();
}

void readFromFile(double & inc) {
	std::ifstream myfile;
  	myfile.open("ex.txt");
  	std::string line;
	if (myfile.is_open()){
	     getline (myfile,line);
	     inc = std::stod(line);
	    myfile.close();
	  }
}

int main(int argc, char ** argv)
{
    glutInit(&argc, argv);
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(WINDOW_W, WINDOW_H);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
    
    glutCreateWindow("Projeto 2.16 - PG");
    glClearColor(1.0, 0.0, 0.0, 0.0);
    glMatrixMode(GL_MODELVIEW); 
    glLoadIdentity();
    
    readFromFile(inc); //Le o parametro que controla a quantidade de pontos avaliados
    glutDisplayFunc(display);
    glutKeyboardFunc(handleKeypress);
    glutMouseFunc(handleMouseClick);
    glutReshapeFunc(reshape);
    
    glutMainLoop();
    
//Para gerar um arquivo .out, ir no term. Linux e colar g++ -std=c++11  main.cpp -lg -lglut -lGL -lGLU -lm

    return 0;
}
