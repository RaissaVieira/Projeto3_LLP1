#ifndef DETECTOR_DE_ROSTOS
#define DETECTOR_DE_ROSTOS

#include <iostream>
#include "opencv2/objdetect.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/videoio.hpp"
#include <ctime>

using namespace std;
using namespace cv;

int cor_detectada = 0;
int pontuacao_atual = 0;

class DetectorDeRostos
{
    private:
    string cascadeName;
    string nestedCascadeName;
    Mat fruta;
    public:
    void detectAndDraw( Mat& img, CascadeClassifier& cascade,
                    CascadeClassifier& nestedCascade,
                    double scale, time_t tempo_anterior, const int cor_atual)
        {
            static int frames = 0;
            double t = 0;
            vector<Rect> faces, faces2;
            const static Scalar colors[] =
            {
                Scalar(255,0,0),
                Scalar(255,128,0),
                Scalar(255,255,0),
                Scalar(0,255,0),
                Scalar(0,128,255),
                Scalar(0,255,255),
                Scalar(0,0,255),
                Scalar(255,0,255)
            };
            Mat gray, smallImg;

            cvtColor( img, gray, COLOR_BGR2GRAY );
            double fx = 1 / scale;
            resize( gray, smallImg, Size(), fx, fx, INTER_LINEAR_EXACT );
            equalizeHist( smallImg, smallImg );

            t = (double)getTickCount();
            cascade.detectMultiScale( smallImg, faces,
                1.2, 2, 0
                //|CASCADE_FIND_BIGGEST_OBJECT
                //|CASCADE_DO_ROUGH_SEARCH
                |CASCADE_SCALE_IMAGE,
                Size(30, 30) );

            frames++;

            if (frames % 30 == 0)
                system("mplayer /usr/lib/libreoffice/share/gallery/sounds/kling.wav &");

            t = (double)getTickCount() - t;
        //    printf( "detection time = %g ms\n", t*1000/getTickFrequency());
            //std::cout << "Restam " << 5 - (time(NULL) - tempo_anterior) << "segundos" <<  std::endl;
                
            
            if(time(NULL) - tempo_anterior > 5)
            {
                for ( size_t i = 0; i < faces.size(); i++ )
                {
                    Rect r = faces[i];
                    //OBTENDO AS COORDENADAS DO CENTRO DO RETÂNGULO
                    double centerX = r.x + 0.5 * r.width;
                    double centerY = r.y + 0.5 * r.height;

                    //---------------------------------------------
                    //printf( "[%3f, %3f]\n", centerX, centerY);//Exibindo as coordenadas do centro do retângulo
                    
                    
                    if(centerX < 330)
                    {
                        if(centerY < 270)
                        {
                            printf("Vermelho\n");
                            cor_detectada = 1;
                        }else//Senão for menor, então é maior ou igual a 270
                        {
                            printf("Azul\n"); 
                            cor_detectada = 3;
                        }
                        
                    }else//Se não for menor, então é maior ou igual a 330
                    {
                        if(centerY < 270)
                        {
                            printf("Verde\n");
                            cor_detectada = 2;
                        }else//Senão for menor, então é maior ou igual a 270
                        {
                            printf("Amarelo\n"); 
                            cor_detectada = 4;
                        }
                    }

                
            

                    /*
                        Anotações:
                        Façamos o centro, no eixo y, como sendo 270.
                        Façamos o centro, no eixo x, como sendo 330.

                        A tela será dividida da seguinte forma:

                        ___________________________             
                        |             |             |
                        |             |             |
                        |   Vermelho  |   Verde     |
                        |             |             |
                        |_____________|_____________|270y
                        |             |             |
                        |             |             |
                        |   Azul      |   Amarelo   |
                        |             |             |
                        |_____________|_____________|
                                    330x

                        Então:
                            Se x < 330 e y < 270 , então está no Vermelho
                            Se x < 330 e y > 270 , então está no Azul
                            Se x > 330 e y < 270 , então está no Verde
                            Se x > 330 e y > 270 , então está no Amarelo



                    */
                    Mat smallImgROI;
                    vector<Rect> nestedObjects;
                    Point center;
                    Scalar color = colors[i%8];
                    int radius;

                    rectangle( img, Point(cvRound(r.x*scale), cvRound(r.y*scale)),
                            Point(cvRound((r.x + r.width-1)*scale), cvRound((r.y + r.height-1)*scale)),
                            color, 3, 8, 0);
                    if( nestedCascade.empty() )
                        continue;
                    smallImgROI = smallImg( r );
                    nestedCascade.detectMultiScale( smallImgROI, nestedObjects,
                        1.1, 2, 0
                        //|CASCADE_FIND_BIGGEST_OBJECT
                        //|CASCADE_DO_ROUGH_SEARCH
                        //|CASCADE_DO_CANNY_PRUNING
                        |CASCADE_SCALE_IMAGE,
                        Size(30, 30) );
                    for ( size_t j = 0; j < nestedObjects.size(); j++ )
                    {
                        Rect nr = nestedObjects[j];
                        center.x = cvRound((r.x + nr.x + nr.width*0.5)*scale);
                        center.y = cvRound((r.y + nr.y + nr.height*0.5)*scale);
                        radius = cvRound((nr.width + nr.height)*0.25*scale);
                        circle( img, center, radius, color, 3, 8, 0 );
                    }
                }
            }

            if (!fruta.empty())
                drawTransparency2(img, fruta, 20, 20);

            cv::putText(img, //target image
                to_string(pontuacao_atual)+" PONTOS", //text
                cv::Point(465, 465), //top-left position
                cv::FONT_HERSHEY_DUPLEX,
                1.0,
                CV_RGB(255, 255, 255), //font color
                2);
        
            time_t tempo_restante = 5 - (time(NULL) - tempo_anterior);
            string tempo_para_exibir = "0";
            if(tempo_restante > 0)
            {
                tempo_para_exibir = to_string(tempo_restante);
            }
            
            cv::putText(img, //target image
                "Restam " + tempo_para_exibir+" Segundos", //text
                cv::Point(0, 465), //top-left position
                cv::FONT_HERSHEY_DUPLEX,
                1.0,
                CV_RGB(255, 255, 255), //font color
                2);

            imshow( "result", img );
        }

        /**
         * @brief Draws a transparent image over a frame Mat.
         * 
         * @param frame the frame where the transparent image will be drawn
         * @param transp the Mat image with transparency, read from a PNG image, with the IMREAD_UNCHANGED flag
         * @param xPos x position of the frame image where the image will start.
         * @param yPos y position of the frame image where the image will start.
         */
        void drawTransparency(Mat frame, Mat transp, int xPos, int yPos) {
            Mat mask;
            vector<Mat> layers;
            
            split(transp, layers); // seperate channels
            Mat rgb[3] = { layers[0],layers[1],layers[2] };
            mask = layers[3]; // png's alpha channel used as mask
            merge(rgb, 3, transp);  // put together the RGB channels, now transp insn't transparent 
            transp.copyTo(frame.rowRange(yPos, yPos + transp.rows).colRange(xPos, xPos + transp.cols), mask);
        }

        void drawTransparency2(Mat frame, Mat transp, int xPos, int yPos) {
            Mat mask;
            vector<Mat> layers;
            
            split(transp, layers); // seperate channels
            Mat rgb[3] = { layers[0],layers[1],layers[2] };
            mask = layers[3]; // png's alpha channel used as mask
            merge(rgb, 3, transp);  // put together the RGB channels, now transp insn't transparent 
            Mat roi1 = frame(Rect(xPos, yPos, transp.cols, transp.rows));
            Mat roi2 = roi1.clone();
            transp.copyTo(roi2.rowRange(0, transp.rows).colRange(0, transp.cols), mask);
            //printf("%p, %p\n", roi1.data, roi2.data);
            double alpha = 0.9;
            addWeighted(roi2, alpha, roi1, 1.0 - alpha, 0.0, roi1);
        }

        int _faceCapture(int pontuacao, const int cor_atual)
        {
            VideoCapture capture;
            Mat frame, image;
            time_t tempo_anterior;
            pontuacao_atual = pontuacao;
            string inputName;
            CascadeClassifier cascade, nestedCascade;
            double scale = 1;
            cor_detectada = 0;
            fruta = cv::imread("Genius_t.png", IMREAD_UNCHANGED);
            if (fruta.empty())
                printf("Error opening file Genius.png\n");
            //É preciso alterar essa linha, para o caminho da pasta como estiver no seu computador
            string folder = "/home/lucas/Downloads/opencv-4.1.2/data/haarcascades/";
            cascadeName = folder + "haarcascade_frontalface_alt.xml";
            nestedCascadeName = folder + "haarcascade_eye_tree_eyeglasses.xml";
            inputName = "/dev/video0";
            //inputName = inputName = "video2019.2.mp4";

            if (!nestedCascade.load(samples::findFileOrKeep(nestedCascadeName)))
                cerr << "WARNING: Could not load classifier cascade for nested objects" << endl;
            if (!cascade.load(samples::findFile(cascadeName)))
            {
                cerr << "ERROR: Could not load classifier cascade" << endl;
                return -1;
            }

            if(!capture.open(inputName))
            {
                cout << "Capture from camera #" <<  inputName << " didn't work" << endl;
                return 1;
            }
            if( capture.isOpened() )
            {
                cout << "Video capturing has been started ..." << endl;
                tempo_anterior = time(NULL);
                for(;;)
                {
                    capture >> frame;
                    if(frame.empty() )
                        break;
                    //Mat frame1 = frame.clone();

                    detectAndDraw( frame, cascade, nestedCascade, scale, tempo_anterior, cor_atual);
                    

                    if(cor_detectada != 0)
                    {

                        break;
                    }
                
                    

                    char c = (char)waitKey(10);
                    if( c == 27 || c == 'q' || c == 'Q' )
                        break;
                }
            }
            
            return cor_detectada;

        }
};



#endif