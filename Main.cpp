//---------------------------------------------------------------------------
#include <iostream>
#include <fstream>
#include <vcl.h>
#include <math.h>
#pragma hdrstop

#include "Main.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
 void TForm1::ColourNoise(int i, int j, int width, int height, int level)
{
        int colors[16], count [16];
        int ttlcolor, theColor;
        int k, l, m, aPixel;

        // Initalize arrays
        for(k=0;k<16;k++)
        {
             colors[k]=-1;
             count[k]=0;
        }

        // Analysis 3X3 space

        switch(level) {
                case 1:
                        for(k=0;k<3 && k+i<width; k++)
                        {
                                for(l=0;l<3 && l+j<height; l++)
                                {
                                        aPixel = ImageGray->Canvas->Pixels[i+k][j+l];
                                        for(m=0;m<16 && colors[m]!=-1 && colors[m]!=aPixel;m++);
                                        if (m<16)
                                        {
                                                if (colors[m]==-1) colors[m] = aPixel;
                                                count[m]++;
                                        }
                                }
                        }
                        break;
                case 2:
                        for(k=0;k<3 && k+i<width; k++)
                        {
                                for(l=0;l<3 && l+j<height; l++)
                                {
                                        aPixel = ImageComplete->Canvas->Pixels[i+k][j+l];
                                        for(m=0;m<16 && colors[m]!=-1 && colors[m]!=aPixel;m++);
                                        if (m<16)
                                        {
                                                if (colors[m]==-1) colors[m] = aPixel;
                                                count[m]++;
                                        }
                                }
                        }
                        break;
        }


        // Copy into next Image

        for(ttlcolor=0;ttlcolor<16 && colors[ttlcolor]!=-1;ttlcolor++);

        if (ttlcolor==1) theColor = clBlack;
        else theColor = clWhite;

        openLine += IntToStr(ttlcolor);
        /*
        for(k=0;k<3 && k+i<width; k++)
          for(l=0;l<3 && l+j<height; l++)
                switch (level) {
                        case 1: Image3->Canvas->Pixels[i+k][j+l] = theColor;
                                break;
                        case 2: Image3->Canvas->Pixels[i+k][j+1] = theColor;
                                break;
                }
        */
}
//---------------------------------------------------------------------------
void TForm1::CenterSurround(int i, int j, int width, int height, int level)
{
        float surroundColorSum;
        float surroundColorAvrg;
        float centerPixel;
        int pixelValue;

        // Out of bounds, do not calculate
        if (i+2>width || j+2>height) return;

        // Analysis 3X3 space

        switch (level) {
                case 1: surroundColorSum = 0;
                        surroundColorSum += (ImageGray->Canvas->Pixels[i+0][j+0]+ImageGray->Canvas->Pixels[i+1][j+0]+ImageGray->Canvas->Pixels[i+2][j+0]);
                        surroundColorSum += (ImageGray->Canvas->Pixels[i+0][j+1]+                                   +ImageGray->Canvas->Pixels[i+2][j+1]);
                        surroundColorSum += (ImageGray->Canvas->Pixels[i+0][j+2]+ImageGray->Canvas->Pixels[i+1][j+2]+ImageGray->Canvas->Pixels[i+2][j+2]);

                        surroundColorAvrg = surroundColorSum / 8.0;

                        centerPixel = ImageGray->Canvas->Pixels[i+1][j+1];
                        break;
                case 2: surroundColorSum = 0;
                        surroundColorSum += (ImageComplete->Canvas->Pixels[i+0][j+0]+ImageComplete->Canvas->Pixels[i+1][j+0]+ImageComplete->Canvas->Pixels[i+2][j+0]);
                        surroundColorSum += (ImageComplete->Canvas->Pixels[i+0][j+1]+                                       +ImageComplete->Canvas->Pixels[i+2][j+1]);
                        surroundColorSum += (ImageComplete->Canvas->Pixels[i+0][j+2]+ImageComplete->Canvas->Pixels[i+1][j+2]+ImageComplete->Canvas->Pixels[i+2][j+2]);

                        surroundColorAvrg = surroundColorSum / 8.0;

                        centerPixel = ImageComplete->Canvas->Pixels[i+1][j+1];
                        break;
        }

        //pixelValue = centerPixel - (int) surroundColorAvrg;
        if (centerPixel <= surroundColorAvrg) pixelValue = clBlack;
        else pixelValue = clWhite;

        // Copy into next Image
        if (pixelValue == clBlack) edgesLine+="0";
        else edgesLine+="1";
        /*
        switch (level) {
                case 1: Image3->Canvas->Pixels[i+1][j+1] = pixelValue;
                        break;
                case 2: Image3->Canvas->Pixels[i+1][j+1] = pixelValue;
                        break;
        } */
}
//---------------------------------------------------------------------------
void TForm1::VerticalNoise(int i, int j, int width, int height, int level)
{
        float verticalSumR;
        float verticalSumL;
        float verticalAvrgR;
        float verticalAvrgL;
        float remainderSumR;
        float remainderSumL;
        float remainderAvrgR;
        float remainderAvrgL;

        // Out of bounds, do not calculate
        if (i+2>width || j+2>height) return;

        // Analysis 3X3 space

        switch (level) {
                case 1: verticalSumR = 0.0;
                        verticalSumR += (ImageGray->Canvas->Pixels[i+2][j+0]+ImageGray->Canvas->Pixels[i+2][j+1]+ImageGray->Canvas->Pixels[i+2][j+2]);
                        verticalAvrgR = verticalSumR / 3.0;

                        verticalSumL = 0.0;
                        verticalSumL += (ImageGray->Canvas->Pixels[i+0][j+0]+ImageGray->Canvas->Pixels[i+0][j+1]+ImageGray->Canvas->Pixels[i+0][j+2]);
                        verticalAvrgL = verticalSumL / 3.0;

                        remainderSumR = 0.0;
                        remainderSumR += (ImageGray->Canvas->Pixels[i+0][j+0]+ImageGray->Canvas->Pixels[i+1][j+0]);
                        remainderSumR += (ImageGray->Canvas->Pixels[i+0][j+1]+ImageGray->Canvas->Pixels[i+1][j+1]);
                        remainderSumR += (ImageGray->Canvas->Pixels[i+0][j+2]+ImageGray->Canvas->Pixels[i+1][j+2]);
                        remainderAvrgR = remainderSumR / 6.0;

                        remainderSumL = 0.0;
                        remainderSumL += (ImageGray->Canvas->Pixels[i+1][j+0]+ImageGray->Canvas->Pixels[i+2][j+0]);
                        remainderSumL += (ImageGray->Canvas->Pixels[i+1][j+1]+ImageGray->Canvas->Pixels[i+2][j+1]);
                        remainderSumL += (ImageGray->Canvas->Pixels[i+1][j+2]+ImageGray->Canvas->Pixels[i+2][j+2]);
                        remainderAvrgL = remainderSumL / 6.0;
                        break;
                case 2: verticalSumR = 0.0;
                        verticalSumR += (ImageComplete->Canvas->Pixels[i+2][j+0]+ImageComplete->Canvas->Pixels[i+2][j+1]+ImageComplete->Canvas->Pixels[i+2][j+2]);
                        verticalAvrgR = verticalSumR / 3.0;

                        verticalSumL = 0.0;
                        verticalSumL += (ImageComplete->Canvas->Pixels[i+0][j+0]+ImageComplete->Canvas->Pixels[i+0][j+1]+ImageComplete->Canvas->Pixels[i+0][j+2]);
                        verticalAvrgL = verticalSumL / 3.0;

                        remainderSumR = 0.0;
                        remainderSumR += (ImageComplete->Canvas->Pixels[i+0][j+0]+ImageComplete->Canvas->Pixels[i+1][j+0]);
                        remainderSumR += (ImageComplete->Canvas->Pixels[i+0][j+1]+ImageComplete->Canvas->Pixels[i+1][j+1]);
                        remainderSumR += (ImageComplete->Canvas->Pixels[i+0][j+2]+ImageComplete->Canvas->Pixels[i+1][j+2]);
                        remainderAvrgR = remainderSumR / 6.0;

                        remainderSumL = 0.0;
                        remainderSumL += (ImageComplete->Canvas->Pixels[i+1][j+0]+ImageComplete->Canvas->Pixels[i+2][j+0]);
                        remainderSumL += (ImageComplete->Canvas->Pixels[i+1][j+1]+ImageComplete->Canvas->Pixels[i+2][j+1]);
                        remainderSumL += (ImageComplete->Canvas->Pixels[i+1][j+2]+ImageComplete->Canvas->Pixels[i+2][j+2]);
                        remainderAvrgL = remainderSumL / 6.0;
                        break;
        }

        // Copy into next Image
        /*
        switch (level) {
                case 1: if (verticalAvrgR > remainderAvrgR) Image3->Canvas->Pixels[i+2][j+1] = clWhite;
                        else Image3->Canvas->Pixels[i+2][j+1] = clBlack;

                        if (verticalAvrgL > remainderAvrgL) Image3->Canvas->Pixels[i+0][j+1] = clWhite;
                        else Image3->Canvas->Pixels[i+0][j+1] = clBlack;
                        break;
                case 2: if (verticalAvrgR > remainderAvrgR) Image3->Canvas->Pixels[i+2][j+1] = clWhite;
                        else Image3->Canvas->Pixels[i+2][j+1] = clBlack;

                        if (verticalAvrgL > remainderAvrgL) Image3->Canvas->Pixels[i+0][j+1] = clWhite;
                        else Image3->Canvas->Pixels[i+0][j+1] = clBlack;
                        break;
        } */

        if (verticalAvrgL > remainderAvrgL) verticalLine+="1";
        else verticalLine+="0";
}
//---------------------------------------------------------------------------
void TForm1::HorizontalNoise(int i, int j, int width, int height, int level)
{
        float horizontalSumT;
        float horizontalSumB;
        float horizontalAvrgT;
        float horizontalAvrgB;
        float remainderSumT;
        float remainderSumB;
        float remainderAvrgT;
        float remainderAvrgB;

        // Out of bounds, do not calculate
        if (i+2>width || j+2>height) return;

        // Analysis 3X3 space

        switch (level) {
                case 1: horizontalSumT = 0.0;
                        horizontalSumT += (ImageGray->Canvas->Pixels[i+0][j+0]+ImageGray->Canvas->Pixels[i+1][j+0]+ImageGray->Canvas->Pixels[i+2][j+0]);
                        horizontalAvrgT = horizontalSumT / 3.0;

                        horizontalSumB = 0.0;
                        horizontalSumB += (ImageGray->Canvas->Pixels[i+0][j+2]+ImageGray->Canvas->Pixels[i+1][j+2]+ImageGray->Canvas->Pixels[i+2][j+2]);
                        horizontalAvrgB = horizontalSumB / 3.0;

                        remainderSumT = 0.0;
                        remainderSumT += (ImageGray->Canvas->Pixels[i+0][j+1]+ImageGray->Canvas->Pixels[i+1][j+1]+ImageGray->Canvas->Pixels[i+2][j+1]);
                        remainderSumT += (ImageGray->Canvas->Pixels[i+0][j+2]+ImageGray->Canvas->Pixels[i+1][j+2]+ImageGray->Canvas->Pixels[i+2][j+2]);
                        remainderAvrgT = remainderSumT / 6.0;

                        remainderSumB = 0.0;
                        remainderSumT += (ImageGray->Canvas->Pixels[i+0][j+0]+ImageGray->Canvas->Pixels[i+1][j+0]+ImageGray->Canvas->Pixels[i+2][j+0]);
                        remainderSumT += (ImageGray->Canvas->Pixels[i+0][j+1]+ImageGray->Canvas->Pixels[i+1][j+1]+ImageGray->Canvas->Pixels[i+2][j+1]);
                        remainderAvrgB = remainderSumB / 6.0;
                        break;
                case 2: horizontalSumT = 0.0;
                        horizontalSumT += (ImageComplete->Canvas->Pixels[i+0][j+0]+ImageComplete->Canvas->Pixels[i+1][j+0]+ImageComplete->Canvas->Pixels[i+2][j+0]);
                        horizontalAvrgT = horizontalSumT / 3.0;

                        horizontalSumB = 0.0;
                        horizontalSumB += (ImageComplete->Canvas->Pixels[i+0][j+2]+ImageComplete->Canvas->Pixels[i+1][j+2]+ImageComplete->Canvas->Pixels[i+2][j+2]);
                        horizontalAvrgB = horizontalSumB / 3.0;

                        remainderSumT = 0.0;
                        remainderSumT += (ImageComplete->Canvas->Pixels[i+0][j+1]+ImageComplete->Canvas->Pixels[i+1][j+1]+ImageComplete->Canvas->Pixels[i+2][j+1]);
                        remainderSumT += (ImageComplete->Canvas->Pixels[i+0][j+2]+ImageComplete->Canvas->Pixels[i+1][j+2]+ImageComplete->Canvas->Pixels[i+2][j+2]);
                        remainderAvrgT = remainderSumT / 6.0;

                        remainderSumB = 0.0;
                        remainderSumT += (ImageComplete->Canvas->Pixels[i+0][j+0]+ImageComplete->Canvas->Pixels[i+1][j+0]+ImageComplete->Canvas->Pixels[i+2][j+0]);
                        remainderSumT += (ImageComplete->Canvas->Pixels[i+0][j+1]+ImageComplete->Canvas->Pixels[i+1][j+1]+ImageComplete->Canvas->Pixels[i+2][j+1]);
                        remainderAvrgB = remainderSumB / 6.0;
                        break;
        }

        // Copy into next Image
        /*
        switch (level) {
                case 1: if (horizontalAvrgT > remainderAvrgT) Image3->Canvas->Pixels[i+1][j+0] = clWhite;
                        else Image3->Canvas->Pixels[i+1][j+0] = clBlack;

                        if (horizontalAvrgB > remainderAvrgB) Image3->Canvas->Pixels[i+1][j+2] = clWhite;
                        else Image3->Canvas->Pixels[i+1][j+2] = clBlack;
                        break;
                case 2: if (horizontalAvrgT > remainderAvrgT) Image3->Canvas->Pixels[i+1][j+0] = clWhite;
                        else Image3->Canvas->Pixels[i+1][j+0] = clBlack;

                        if (horizontalAvrgB > remainderAvrgB) Image3->Canvas->Pixels[i+1][j+2] = clWhite;
                        else Image3->Canvas->Pixels[i+1][j+2] = clBlack;
                        break;
        } */

       if (horizontalAvrgT > remainderAvrgT) horizontalLine+="1";
       else horizontalLine+="0";
}
//---------------------------------------------------------------------------
void TForm1::GeneralNoise(int i, int j, int width, int height, int level)
{
        int pixelValue;
        int points;

        // Out of bounds, do not calculate
        if (i+2>width || j+2>height) return;

        // Analysis 3X3 space

        points=0;

        switch (level) {
                case 1: if (ImageGray->Canvas->Pixels[i+0][j+0]>ImageGray->Canvas->Pixels[i+1][j+0]) points++;
                        if (ImageGray->Canvas->Pixels[i+1][j+0]<ImageGray->Canvas->Pixels[i+2][j+0]) points++;
                        if (ImageGray->Canvas->Pixels[i+0][j+1]<ImageGray->Canvas->Pixels[i+1][j+1]) points++;
                        if (ImageGray->Canvas->Pixels[i+1][j+1]>ImageGray->Canvas->Pixels[i+2][j+1]) points++;
                        if (ImageGray->Canvas->Pixels[i+0][j+2]>ImageGray->Canvas->Pixels[i+1][j+2]) points++;
                        if (ImageGray->Canvas->Pixels[i+1][j+2]<ImageGray->Canvas->Pixels[i+2][j+2]) points++;
                        break;
                case 2: if (ImageComplete->Canvas->Pixels[i+0][j+0]>ImageComplete->Canvas->Pixels[i+1][j+0]) points++;
                        if (ImageComplete->Canvas->Pixels[i+1][j+0]<ImageComplete->Canvas->Pixels[i+2][j+0]) points++;
                        if (ImageComplete->Canvas->Pixels[i+0][j+1]<ImageComplete->Canvas->Pixels[i+1][j+1]) points++;
                        if (ImageComplete->Canvas->Pixels[i+1][j+1]>ImageComplete->Canvas->Pixels[i+2][j+1]) points++;
                        if (ImageComplete->Canvas->Pixels[i+0][j+2]>ImageComplete->Canvas->Pixels[i+1][j+2]) points++;
                        if (ImageComplete->Canvas->Pixels[i+1][j+2]<ImageComplete->Canvas->Pixels[i+2][j+2]) points++;
                        break;
        }

        // Copy into next Image

        if (points > 3) pixelValue = clWhite;
        else pixelValue = clBlack;
        /*
        switch (level) {
                case 1: Image3->Canvas->Pixels[i+1][j+1] = pixelValue;
                        break;
                case 2: Image3->Canvas->Pixels[i+1][j+1] = pixelValue;
                        break;
        } */

       if (pixelValue == clBlack) generalLine+="0";
       else generalLine+="1";
}
//---------------------------------------------------------------------------
void TForm1::DiagonalNoise(int i, int j, int width, int height, int level)
{
        int pixelValue;
        float diagSumR;
        float diagAvrgR;
        float diagSumL;
        float diagAvrgL;
        float remainderSumR;
        float remainderAvrgR;
        float remainderSumL;
        float remainderAvrgL;

        // Out of bounds, do not calculate
        if (i+2>width || j+2>height) return;

        // Analysis 3X3 space
        switch (level) {
                case 1: diagSumR = 0.0;
                        diagSumR = ImageGray->Canvas->Pixels[i+2][j+0]+ImageGray->Canvas->Pixels[i+1][j+1]+ImageGray->Canvas->Pixels[i+0][j+2];
                        diagAvrgR = diagSumR / 3.0;

                        remainderSumR = 0.0;
                        remainderSumR = ImageGray->Canvas->Pixels[i+0][j+0]+ImageGray->Canvas->Pixels[i+1][j+0]+
                                        ImageGray->Canvas->Pixels[i+0][j+1]+ImageGray->Canvas->Pixels[i+2][j+1]+
                                        ImageGray->Canvas->Pixels[i+1][j+2]+ImageGray->Canvas->Pixels[i+2][j+2];
                        remainderAvrgR = remainderSumR / 6.0;

                        diagSumL = 0.0;
                        diagSumL = ImageGray->Canvas->Pixels[i+0][j+0]+ImageGray->Canvas->Pixels[i+1][j+1]+ImageGray->Canvas->Pixels[i+2][j+2];
                        diagAvrgL = diagSumL / 3.0;

                        remainderSumL = 0.0;
                        remainderSumL = ImageGray->Canvas->Pixels[i+1][j+0]+ImageGray->Canvas->Pixels[i+2][j+0]+
                                        ImageGray->Canvas->Pixels[i+0][j+1]+ImageGray->Canvas->Pixels[i+2][j+1]+
                                        ImageGray->Canvas->Pixels[i+0][j+2]+ImageGray->Canvas->Pixels[i+1][j+2];
                        remainderAvrgL = remainderSumL / 6.0;
                        break;
                case 2: diagSumR = 0.0;
                        diagSumR = ImageComplete->Canvas->Pixels[i+2][j+0]+ImageComplete->Canvas->Pixels[i+1][j+1]+ImageComplete->Canvas->Pixels[i+0][j+2];
                        diagAvrgR = diagSumR / 3.0;

                        remainderSumR = 0.0;
                        remainderSumR = ImageComplete->Canvas->Pixels[i+0][j+0]+ImageComplete->Canvas->Pixels[i+1][j+0]+
                                        ImageComplete->Canvas->Pixels[i+0][j+1]+ImageComplete->Canvas->Pixels[i+2][j+1]+
                                        ImageComplete->Canvas->Pixels[i+1][j+2]+ImageComplete->Canvas->Pixels[i+2][j+2];
                        remainderAvrgR = remainderSumR / 6.0;

                        diagSumL = 0.0;
                        diagSumL = ImageComplete->Canvas->Pixels[i+0][j+0]+ImageComplete->Canvas->Pixels[i+1][j+1]+ImageComplete->Canvas->Pixels[i+2][j+2];
                        diagAvrgL = diagSumL / 3.0;

                        remainderSumL = 0.0;
                        remainderSumL = ImageComplete->Canvas->Pixels[i+1][j+0]+ImageComplete->Canvas->Pixels[i+2][j+0]+
                                        ImageComplete->Canvas->Pixels[i+0][j+1]+ImageComplete->Canvas->Pixels[i+2][j+1]+
                                        ImageComplete->Canvas->Pixels[i+0][j+2]+ImageComplete->Canvas->Pixels[i+1][j+2];
                        remainderAvrgL = remainderSumL / 6.0;
                        break;
        }

        // Copy into next Image
        if (diagAvrgR > remainderAvrgR || diagAvrgL > remainderAvrgL) pixelValue = clWhite;
        else pixelValue = clBlack;
        /*
        switch (level) {
                case 1: Image3->Canvas->Pixels[i+1][j+1] = pixelValue;
                        break;
                case 2: Image3->Canvas->Pixels[i+1][j+1] = pixelValue;
                        break;
        } */

       if (pixelValue == clBlack) diagonalLine+="0";
       else diagonalLine+="1";
}
//---------------------------------------------------------------------------
AnsiString TForm1::NoiseAvrg(int i, int j, int size, AnsiString line1, AnsiString line2, AnsiString line3, AnsiString line4, AnsiString line5, bool average)
{
        int k, value, sum=0, avrg=0;

        if (size != 3 && size != 5) {ShowMessage("Size not 3 or 5");return "X";}

        if (line1.Length() < 4) return "X"; // We do not have enough data
        if (line2.Length() < 4) return "X";
        if (line3.Length() < 4) return "X";
        if (size == 5 && line4.Length() < 4) return "X";
        if (size == 5 && line5.Length() < 4) return "X";

        if (line1.Length()>i+size)
        {
          for(k=1;k<=size;k++)
          {
                value = line1[i+k]-'0';
                sum+=value;
          }
          for(k=1;k<=size;k++)
          {
                value = line2[i+k]-'0';
                sum+=value;
          }
          for(k=1;k<=size;k++)
          {
                value = line3[i+k]-'0';
                sum+=value;
          }

          if (size == 5)
          {
            for(k=1;k<=size;k++)
            {
                value = line4[i+k]-'0';
                sum+=value;
            }
            for(k=1;k<=size;k++)
            {
                value = line5[i+k]-'0';
                sum+=value;
            }
          }
        }

        if (average)
        {
          if (size == 3) avrg = sum / 9;
          else avrg = sum / 25;
        }
        else
        {
          if (size == 3) avrg = (sum>=EditLimit9->Text.ToIntDef(4))? 1: 0;
          else avrg = (sum>=EditLimit25->Text.ToIntDef(11))? 1: 0;
        }

return IntToStr(avrg);
}

//---------------------------------------------------------------------------
void __fastcall TForm1::BitBtn2Click(TObject *Sender)
{
        //Image1->Canvas->Brush->Color = clBlack;
        //Image1->Canvas->Rectangle(10,10,50,50);
        //Image1->Canvas->Pixels[52][52] = clWhite;

        int imageFeatures[3][9];
        int imageFeaturesOld[3][9];

	int verticalLines[1000][4];
	int horizontalLines[1000][4];
	int numvlines,numhlines,jump,window;

	numvlines=0;
	numhlines=0;

        float x = 0;
        float s = 0;
        int v0,v1,v2,v3;
        char dchar,hchar,vchar;

        float p1,p2;
        int threshold;

        float rowsize, columnsize, boxsize;

        int width  = Image1->Picture->Bitmap->Width;
        int height = Image1->Picture->Bitmap->Height;
        int i, j, k;

        AnsiString oLine1, oLine2, oLine3, oLine4, oLine5;
        AnsiString vLine1, vLine2, vLine3, vLine4, vLine5;
        AnsiString hLine1, hLine2, hLine3, hLine4, hLine5;
        AnsiString dLine1, dLine2, dLine3, dLine4, dLine5;
        AnsiString gLine1, gLine2, gLine3, gLine4, gLine5;
        AnsiString eLine1, eLine2, eLine3, eLine4, eLine5;

        int **pixelScore;
        pixelScore = (int**) malloc(width*sizeof(int*));
        // initialization
        for (i=0;i<width;i++)
                pixelScore[i] = (int*) malloc(height*sizeof(int));

        for(j=0;j<height;j++)
                for(i=0;i<width;i++)
                        pixelScore[i][j] = 0;

        for (i=0; i<5; i++)
                for (j=0; j<9; j++)
                        imageFeaturesOld[i][j] = 0;

        for (i=0; i<5; i++)
                for (j=0; j<9; j++)
                        imageFeatures[i][j] = 0;

        // set up progression abr and init
        ProgressBar1->Max = width*height;
        ProgressBar1->Position = 0;


        // clear everything line inside 12 text panel (on right hand side)
        MemoOpen->Lines->Clear();
        MemoVertical->Lines->Clear();
        MemoHorizontal->Lines->Clear();
        MemoDiagonal->Lines->Clear();
        MemoGeneral->Lines->Clear();
        MemoEdges->Lines->Clear();

        // float  2 input box in middle "upper and lower"
        p1 = editWhite->Text.ToDouble(); // upper
        p2 = editBlack->Text.ToDouble(); // lower

        // input boxes under threshold in the middle
        // int
        v0 = Edit1->Text.ToIntDef(0);
        v1 = Edit2->Text.ToIntDef(0);
        v2 = Edit3->Text.ToIntDef(0);
        v3 = Edit4->Text.ToIntDef(0);

        threshold = Edit5->Text.ToIntDef(0);

        // int
        jump = Edit6->Text.ToIntDef(0);
        window = Edit7->Text.ToIntDef(0);

        // x is average value of the pixel value in the image
        // s is the standard deviation of all pixel values inside the image
        for(j=0;j<height;j++)
                for(i=0;i<width;i++)
                        x += (float) Image1->Canvas->Pixels[i][j];
        x = x/(height*width);

        for (j=0;j<height;j++)
                for(i=0;i<width;i++)
                        s += (Image1->Canvas->Pixels[i][j]-x)*(Image1->Canvas->Pixels[i][j]-x)/(height*width-1.0);
        s = sqrt(s);


        // then determine which oolor shud use (black white gray) to do grating
        for (j=0;j<height;j++)
                for(i=0;i<width;i++)
                        if (Image1->Canvas->Pixels[i][j]>x+p1*s) ImageGray->Canvas->Pixels[i][j]=clWhite;
                        else if (Image1->Canvas->Pixels[i][j]<x-p2*s) ImageGray->Canvas->Pixels[i][j]=clBlack;
                        else ImageGray->Canvas->Pixels[i][j]=clGray;


        //if (Application->MessageBox("Stage 1 - Image Grating Complete. Continue?","Prompt",MB_YESNO)==IDNO) return;

        for(j=0;j<height;j++)
        {
                // each line denotes a type of noise
                openLine="";
                verticalLine="";
                horizontalLine="";
                diagonalLine="";
                generalLine="";
                edgesLine="";

                // image is divided into many horizontal lines of 1 pixel height
                // check for each of noise detection method and output it into textbox (Tmemo)
                // above *Line variable used to store these values.
                // update progression bar accordingly
                for(i=0;i<width;i++)
                {

                   if (CheckBoxColor->Checked && i%3==0 && j%3==0) ColourNoise(i,j,width,height,1);
                   if (CheckBoxCenter->Checked) CenterSurround(i,j,width,height,1);
                   if (CheckBoxVertical->Checked) VerticalNoise(i,j,width,height,1);
                   if (CheckBoxHorizontal->Checked) HorizontalNoise(i,j,width,height,1);
                   if (CheckBoxGeneral->Checked) GeneralNoise(i,j,width,height,1);
                   if (CheckBoxDiag->Checked) DiagonalNoise(i,j,width,height,1);

                }

                if (CheckBoxColor->Checked && i%3==0 && j%3==0) MemoOpen->Lines->Add(openLine);
                if (CheckBoxCenter->Checked) MemoEdges->Lines->Add(edgesLine);
                if (CheckBoxVertical->Checked) MemoVertical->Lines->Add(verticalLine);
                if (CheckBoxHorizontal->Checked) MemoHorizontal->Lines->Add(horizontalLine);
                if (CheckBoxGeneral->Checked) MemoGeneral->Lines->Add(generalLine);
                if (CheckBoxDiag->Checked) MemoDiagonal->Lines->Add(diagonalLine);

                ProgressBar1->Position = (j+1)*width;
        }

        //  the radiobox group in the middle
        // check for each mode 1.open, 2.vertical, 3.horizontal, 4.diagonal, 5.general, 6.edge
        // MemoVertical etc. can be access as a 2D array of characters.
        // and access is as horizontal then vertical like x, y
        // however pixel is vertical then horizontal
        // set pixel in x = i - 1 and y = j into black if memo value of y = j and x =  i - 1 is 0
        // set white for the pixel horizontally before the selected one
        // set white otherwise
        if (RadioGroupGrayScale->ItemIndex==1)  // mode for open noise
                for (j=0; j<height-3; j+=1)
                        for (i=1; i<=width-3; i+=1)
                                if (MemoVertical->Lines->Strings[j][i]=='0') Image->Canvas->Pixels[i-1][j]=clBlack;
                                else Image->Canvas->Pixels[i-1][j]=clWhite;
        if (RadioGroupGrayScale->ItemIndex==2)
                for (j=0; j<height-3; j+=1)
                        for (i=1; i<=width-3; i+=1)
                                if (MemoHorizontal->Lines->Strings[j][i]=='0') Image->Canvas->Pixels[i-1][j]=clBlack;
                                else Image->Canvas->Pixels[i-1][j]=clWhite;
        if (RadioGroupGrayScale->ItemIndex==3)
                for (j=0; j<height-3; j+=1)
                        for (i=1; i<=width-3; i+=1)
                                if (MemoDiagonal->Lines->Strings[j][i]=='0') Image->Canvas->Pixels[i-1][j]=clBlack;
                                else Image->Canvas->Pixels[i-1][j]=clWhite;
        if (RadioGroupGrayScale->ItemIndex==4)
                for (j=0; j<height-3; j+=1)
                        for (i=1; i<=width-3; i+=1)
                                if (MemoGeneral->Lines->Strings[j][i]=='0') Image->Canvas->Pixels[i-1][j]=clBlack;
                                else Image->Canvas->Pixels[i-1][j]=clWhite;
        if (RadioGroupGrayScale->ItemIndex==5)
                for (j=0; j<height-3; j+=1)
                        for (i=1; i<=width-3; i+=1)
                                if (MemoEdges->Lines->Strings[j][i]=='0') Image->Canvas->Pixels[i-1][j]=clBlack;
                                else Image->Canvas->Pixels[i-1][j]=clWhite;

        //ShowMessage("Stage 2 -  Feature Extract Complete.");

        ProgressBar1->Position = 0;

        for(j=0;j<height;j++) {
                for(i=0;i<width;i++)
                        if(Image->Canvas->Pixels[i][j]==clWhite) {
                                int m,n,v;
                                pixelScore[i][j] += v0;
                                for(k=1;k<4;k++) {
                                        if (k==1) v=v1;
                                        else if (k==2) v=v2;
                                        else if (k==3) v=v3;

                                        for(m=i-k;m<=i+k;m++) {
                                                if(m>=0 && m<width && j-k>=0)  pixelScore[m][j-k]+=v;
                                                if(m>=0 && m<width && j+k<height)  pixelScore[m][j+k]+=v;
                                        }
                                        for(n=j-k+1;n<j+k;n++) {
                                                if(i-k>=0 && n>=0 && n<height)   pixelScore[i-k][n]+=v;
                                                if(i+k<width && n>=0 && n<height) pixelScore[i+k][n]+=v;
                                        }
                                }
                        }
                ProgressBar1->Position = (j+1)*width;
        }

        for(j=0;j<height;j++) {
                for(i=0;i<width;i++) {
                        if(pixelScore[i][j]>=threshold) ImageComplete->Canvas->Pixels[i][j]=clWhite;
                        else ImageComplete->Canvas->Pixels[i][j]=clBlack;
                }
        }

        //ShowMessage("Stage 3 - Line Completion complete.");

        ProgressBar1->Position = 0;

        MemoOpenPost->Lines->Clear();
        MemoVerticalPost->Lines->Clear();
        MemoHorizontalPost->Lines->Clear();
        MemoDiagonalPost->Lines->Clear();
        MemoGeneralPost->Lines->Clear();
        MemoEdgesPost->Lines->Clear();

        for(j=0;j<height;j++)
        {
                openLine="";
                verticalLine="";
                horizontalLine="";
                diagonalLine="";
                generalLine="";
                edgesLine="";

                for(i=0;i<width;i++)
                {

                   if (CheckBoxColor->Checked && i%3==0 && j%3==0) ColourNoise(i,j,width,height,2);
                   if (CheckBoxCenter->Checked) CenterSurround(i,j,width,height,2);
                   if (CheckBoxVertical->Checked) VerticalNoise(i,j,width,height,2);
                   if (CheckBoxHorizontal->Checked) HorizontalNoise(i,j,width,height,2);
                   if (CheckBoxGeneral->Checked) GeneralNoise(i,j,width,height,2);
                   if (CheckBoxDiag->Checked) DiagonalNoise(i,j,width,height,2);

                }

                if (CheckBoxColor->Checked && i%3==0 && j%3==0) MemoOpenPost->Lines->Add(openLine);
                if (CheckBoxCenter->Checked) MemoEdgesPost->Lines->Add(edgesLine);
                if (CheckBoxVertical->Checked) MemoVerticalPost->Lines->Add(verticalLine);
                if (CheckBoxHorizontal->Checked) MemoHorizontalPost->Lines->Add(horizontalLine);
                if (CheckBoxGeneral->Checked) MemoGeneralPost->Lines->Add(generalLine);
                if (CheckBoxDiag->Checked) MemoDiagonalPost->Lines->Add(diagonalLine);

                ProgressBar1->Position = (j+1)*width;
        }

        if (RadioGroupLineComplete->ItemIndex==1)
                for (j=0; j<height-3; j+=1)
                        for (i=1; i<=width-3; i+=1)
                                if (MemoVerticalPost->Lines->Strings[j][i]=='0') ImagePost->Canvas->Pixels[i-1][j]=clBlack;
                                else ImagePost->Canvas->Pixels[i-1][j]=clWhite;
        if (RadioGroupLineComplete->ItemIndex==2)
                for (j=0; j<height-3; j+=1)
                        for (i=1; i<=width-3; i+=1)
                                if (MemoHorizontalPost->Lines->Strings[j][i]=='0') ImagePost->Canvas->Pixels[i-1][j]=clBlack;
                                else ImagePost->Canvas->Pixels[i-1][j]=clWhite;
        if (RadioGroupLineComplete->ItemIndex==3)
                for (j=0; j<height-3; j+=1)
                        for (i=1; i<=width-3; i+=1)
                                if (MemoDiagonalPost->Lines->Strings[j][i]=='0') ImagePost->Canvas->Pixels[i-1][j]=clBlack;
                                else ImagePost->Canvas->Pixels[i-1][j]=clWhite;
        if (RadioGroupLineComplete->ItemIndex==4)
                for (j=0; j<height-3; j+=1)
                        for (i=1; i<=width-3; i+=1)
                                if (MemoGeneralPost->Lines->Strings[j][i]=='0') ImagePost->Canvas->Pixels[i-1][j]=clBlack;
                                else ImagePost->Canvas->Pixels[i-1][j]=clWhite;
        if (RadioGroupLineComplete->ItemIndex==5)
                for (j=0; j<height-3; j+=1)
                        for (i=1; i<=width-3; i+=1)
                                if (MemoEdgesPost->Lines->Strings[j][i]=='0') ImagePost->Canvas->Pixels[i-1][j]=clBlack;
                                else ImagePost->Canvas->Pixels[i-1][j]=clWhite;

        //ShowMessage("Stage 4 - Post-processing complete.");

        /*

        ProgressBar1->Position = 0;

        for (j=0;j<height-3;j++)
                for (i=0;i<width;i++)
                        ImageThin->Canvas->Pixels[i][j]=ImageComplete->Canvas->Pixels[i][j];

        switch (RadioBoxThinOptions->ItemIndex)
        {
                case 0:
                        for (i=0;i<width;i++) {
                                for (j=1;j<height-1;j++)
                                        if (ImageThin->Canvas->Pixels[i][j]==clWhite && ImageThin->Canvas->Pixels[i][j-1]==clBlack && ImageThin->Canvas->Pixels[i][j+1]==clWhite)
                                                ImageThin->Canvas->Pixels[i][j]=clBlack;
                                ProgressBar1->Position=(i+1)*width;
                        }
                        break;
                case 1:
                        for (j=0;j<height;j++) {
                                for (i=1;i<width-1;i++)
                                        if (ImageThin->Canvas->Pixels[i][j]==clWhite && ImageThin->Canvas->Pixels[i-1][j]==clBlack && ImageThin->Canvas->Pixels[i+1][j]==clWhite)
                                                ImageThin->Canvas->Pixels[i][j]=clBlack;
                                ProgressBar1->Position=(j+1)*width;
                        }
                        break;
                case 2:
                        for (i=0;i<width;i++) {
                                for (j=1;j<height-1;j++)
                                        if (ImageThin->Canvas->Pixels[i][j]==clWhite && ImageThin->Canvas->Pixels[i][j-1]==clBlack && ImageThin->Canvas->Pixels[i][j+1]==clWhite)
                                                ImageThin->Canvas->Pixels[i][j]=clBlack;
                                ProgressBar1->Position=(i+1)*width;
                        }
                        ProgressBar1->Position = 0;

                        for (j=0;j<height;j++) {
                                for (i=1;i<width-1;i++)
                                        if (ImageThin->Canvas->Pixels[i][j]==clWhite && ImageThin->Canvas->Pixels[i-1][j]==clBlack && ImageThin->Canvas->Pixels[i+1][j]==clWhite)
                                                ImageThin->Canvas->Pixels[i][j]=clBlack;
                                ProgressBar1->Position=(j+1)*height;
                        }
                        break;
                default: break;
        }
        */
        //ShowMessage("Stage 5 - Line Thinning complete.");

        ProgressBar1->Position = 0;

        for(j=0;j<height-3;j++) {
                for(i=1;i<=width-3;i++)
                        if (MemoDiagonal->Lines->Strings[j][i]=='1') ImageColor->Canvas->Pixels[i-1][j]=clYellow;
                        else if (MemoHorizontal->Lines->Strings[j][i]=='1') ImageColor->Canvas->Pixels[i-1][j]=clBlue;
                        else if (MemoVertical->Lines->Strings[j][i]=='1') ImageColor->Canvas->Pixels[i-1][j]=clGreen;
                        else ImageColor->Canvas->Pixels[i-1][j]=clBlack;
                ProgressBar1->Position=(j+1)*width;
        }

        ProgressBar1->Position = 0;

        for(j=0;j<height-3;j++) {
                for(i=1;i<=width-3;i++)
                        if (MemoDiagonalPost->Lines->Strings[j][i]=='1') ImageLines->Canvas->Pixels[i-1][j]=clYellow;
                        else if (MemoHorizontalPost->Lines->Strings[j][i]=='1') ImageLines->Canvas->Pixels[i-1][j]=clBlue;
                        else if (MemoVerticalPost->Lines->Strings[j][i]=='1') ImageLines->Canvas->Pixels[i-1][j]=clGreen;
                        else ImageLines->Canvas->Pixels[i-1][j]=clBlack;
                ProgressBar1->Position=(j+1)*width;
        }

        ProgressBar1->Position = 0;

        for(j=0;j<height-3;j++) {
                for(i=1;i<=width-3;i++)
                        if (MemoDiagonalPost->Lines->Strings[j][i]=='1') ImageColor2->Canvas->Pixels[i-1][j]=clYellow;
                        else if (MemoHorizontalPost->Lines->Strings[j][i]=='1') ImageColor2->Canvas->Pixels[i-1][j]=clBlue;
                        else if (MemoVerticalPost->Lines->Strings[j][i]=='1') ImageColor2->Canvas->Pixels[i-1][j]=clGreen;
                        else ImageColor2->Canvas->Pixels[i-1][j]=clBlack;
                ProgressBar1->Position=(j+1)*width;
        }

        //ShowMessage("Stage 6 - Image Coloring complete");

        ProgressBar1->Max = width*height;
        ProgressBar1->Position = 0;

	for(i=0;i<height;i++) {
		for(j=0;j<width;j++)
			if(ImageLines->Canvas->Pixels[j][i]==clGreen) {
				int topx,topy,bottomx,bottomy;
				int k,l,m,n;

				k=i;
				l=j;

				topx=j;
				topy=i;
				bottomx=j;
				bottomy=i;

				for(n=0;n<=window;n++) {
					for(m=1;m<=jump && !(ImageLines->Canvas->Pixels[l+n][k-m]==clGreen);m++) ;

					if (m<=jump && k>=0) {
						topx=l+n;
						topy=k-m;
						k=k-m;
						l=l+n;
						n=-1;
						continue;
					}

					for(m=1;m<=jump && !(ImageLines->Canvas->Pixels[l-n][k-m]==clGreen);m++) ;

					if (m<=jump && k>=0) {
						topx=l-n;
						topy=k-m;
						k=k-m;
						l = l-n;
						n=-1;
						continue;
					}

				}

				k=i;
				l=j;
				for(n=0;n<=window;n++) {
					for(m=1;m<=jump && !(ImageLines->Canvas->Pixels[l+n][k+m]==clGreen);m++) ;

					if (m<=jump && k<height) {
						bottomx=l+n;
						bottomy=k+m;
						k=k+m;
						l=l+n;
						n=-1;
						continue;
					}

					for(m=1;m<=jump && !(ImageLines->Canvas->Pixels[l-n][k+m]==clGreen);m++) ;

					if (m<=jump && k<height) {
						bottomx=l-n;
						bottomy=k+m;
						k=k+m;
						l = l-n;
						n=-1;
						continue;
					}

				}

                                if (i-topy>threshold || bottomy-i>threshold) {
					for(k=i;k>=topy;k--)
						for(l=j-window;l<=j+window;l++)
							ImageLines->Canvas->Pixels[l][k]=clBlack;
					for(k=i;k<=bottomy;k++)
						for(l=j-window;l<=j+window;l++)
							ImageLines->Canvas->Pixels[l][k]=clBlack;

					verticalLines[numvlines][0] = topx;
					verticalLines[numvlines][1] = topy;
					verticalLines[numvlines][2] = bottomx;
					verticalLines[numvlines][3] = bottomy;

					numvlines++;
				}
                        }
                        else if(ImageLines->Canvas->Pixels[j][i]==clBlue) {
                                int leftx,lefty,rightx,righty;
                                int k,l,m,n;

				k=i;
				l=j;

                                leftx=j;
				lefty=i;
				rightx=j;
				righty=i;

				for(n=0;n<=window;n++) {
					for(m=1;m<=jump && !(ImageLines->Canvas->Pixels[l-m][k+n]==clBlue);m++) ;

					if (m<=jump && l>=0) {
						leftx=l-m;
						lefty=k+n;
						k=k+n;
						l=l-m;
						n=-1;
						continue;
					}

					for(m=1;m<=jump && !(ImageLines->Canvas->Pixels[l-m][k-n]==clBlue);m++) ;

					if (m<=jump && l>=0) {
						leftx=l-m;
						lefty=k-n;
						k=k-n;
						l = l-m;
						n=-1;
						continue;
					}

				}

				for(n=0;n<=window;n++) {
					for(m=1;m<=jump && !(ImageLines->Canvas->Pixels[l+m][k+n]==clBlue);m++) ;

					if (m<=jump && l<width) {
						rightx=l+m;
						righty=k+n;
						k=k+n;
						l=l+m;
						n=-1;
						continue;
					}

					for(m=1;m<=jump && !(ImageLines->Canvas->Pixels[l+m][k-n]==clBlue);m++) ;

					if (m<=jump && l<width) {
						rightx=l+m;
						righty=k-n;
						k=k-n;
						l = l+m;
						n=-1;
						continue;
					}

				}

                                if (j-leftx>threshold || rightx-j>threshold) {
					for(k=i-window;k<=i+window;k++)
						for(l=j;l>=leftx;l--)
							ImageLines->Canvas->Pixels[l][k]=clBlack;
					for(k=i-window;k<=i+window;k++)
						for(l=j;l<=rightx;l++)
							ImageLines->Canvas->Pixels[l][k]=clBlack;

					horizontalLines[numhlines][0] = leftx;
					horizontalLines[numhlines][1] = lefty;
					horizontalLines[numhlines][2] = rightx;
					horizontalLines[numhlines][3] = righty;

					numhlines++;
				}
			}
                ProgressBar1->Position=(i+1)*width;
        }
        
        ImageLines->Canvas->Pen->Color=clGreen;
        for(i=0;i<numvlines;i++) {
                ImageLines->Canvas->MoveTo(verticalLines[i][0],verticalLines[i][1]);
                ImageLines->Canvas->LineTo(verticalLines[i][2],verticalLines[i][3]);
        }

        ImageLines->Canvas->Pen->Color=clBlue;
        for(i=0;i<numhlines;i++) {
                ImageLines->Canvas->MoveTo(horizontalLines[i][0],horizontalLines[i][1]);
                ImageLines->Canvas->LineTo(horizontalLines[i][2],horizontalLines[i][3]);
        }

        //ShowMessage("Stage 7 - Line Draw complete");

        ProgressBar1->Max = width*height;
        ProgressBar1->Position = 0;

        MemoOpenJet->Lines->Clear();
        MemoVerticalJet->Lines->Clear();
        MemoHorizontalJet->Lines->Clear();
        MemoDiagonalJet->Lines->Clear();
        MemoGeneralJet->Lines->Clear();
        MemoEdgesJet->Lines->Clear();

        for(j=0;j<height-3;j++)
        {
                verticalLine="";
                horizontalLine="";
                diagonalLine="";

                for(i=1;i<=width-3;i++)
                {
                        dchar = MemoDiagonalPost->Lines->Strings[j][i];
                        hchar = MemoHorizontalPost->Lines->Strings[j][i];
                        vchar = MemoVerticalPost->Lines->Strings[j][i];

                        diagonalLine+=dchar;

                        if (dchar-'0') horizontalLine+='0';
                        else horizontalLine+=hchar;

                        if (dchar-'0'||hchar-'0') verticalLine+='0';
                        else verticalLine+=vchar;

                }

                if (CheckBoxVertical->Checked) MemoVerticalJet->Lines->Add(verticalLine);
                if (CheckBoxHorizontal->Checked) MemoHorizontalJet->Lines->Add(horizontalLine);
                if (CheckBoxDiag->Checked) MemoDiagonalJet->Lines->Add(diagonalLine);

                ProgressBar1->Position = (j+1)*width;
        }


        for(j=0; j<height-3; j++)
        {
                if (j<height/3)
                {
                        for(i=1; i<=width-3; i++)
                        {
                                if (i<width/3)
                                {
                                        imageFeaturesOld[0][0] += MemoVerticalPost->Lines->Strings[j][i] - '0';
                                        imageFeaturesOld[1][0] += MemoHorizontalPost->Lines->Strings[j][i] - '0';
                                        imageFeaturesOld[2][0] += MemoDiagonalPost->Lines->Strings[j][i] - '0';

                                        imageFeatures[0][0] += MemoVerticalJet->Lines->Strings[j][i] - '0';
                                        imageFeatures[1][0] += MemoHorizontalJet->Lines->Strings[j][i] - '0';
                                        imageFeatures[2][0] += MemoDiagonalJet->Lines->Strings[j][i] - '0';
                                }

                                else if (i>=width/3 && i<2*(width/3))
                                {
                                        imageFeaturesOld[0][1] += MemoVerticalPost->Lines->Strings[j][i] - '0';
                                        imageFeaturesOld[1][1] += MemoHorizontalPost->Lines->Strings[j][i] - '0';
                                        imageFeaturesOld[2][1] += MemoDiagonalPost->Lines->Strings[j][i] - '0';

                                        imageFeatures[0][1] += MemoVerticalJet->Lines->Strings[j][i] - '0';
                                        imageFeatures[1][1] += MemoHorizontalJet->Lines->Strings[j][i] - '0';
                                        imageFeatures[2][1] += MemoDiagonalJet->Lines->Strings[j][i] - '0';
                                }

                                else
                                {
                                        imageFeaturesOld[0][2] += MemoVerticalPost->Lines->Strings[j][i] - '0';
                                        imageFeaturesOld[1][2] += MemoHorizontalPost->Lines->Strings[j][i] - '0';
                                        imageFeaturesOld[2][2] += MemoDiagonalPost->Lines->Strings[j][i] - '0';

                                        imageFeatures[0][2] += MemoVerticalJet->Lines->Strings[j][i] - '0';
                                        imageFeatures[1][2] += MemoHorizontalJet->Lines->Strings[j][i] - '0';
                                        imageFeatures[2][2] += MemoDiagonalJet->Lines->Strings[j][i] - '0';
                                }
                        }
                }

                else if (j>=height/3 && j<2*(height/3))
                {
                        for(i=1; i<=width-3; i++)
                        {
                                if (i<width/3)
                                {
                                        imageFeaturesOld[0][3] += MemoVerticalPost->Lines->Strings[j][i] - '0';
                                        imageFeaturesOld[1][3] += MemoHorizontalPost->Lines->Strings[j][i] - '0';
                                        imageFeaturesOld[2][3] += MemoDiagonalPost->Lines->Strings[j][i] - '0';

                                        imageFeatures[0][3] += MemoVerticalJet->Lines->Strings[j][i] - '0';
                                        imageFeatures[1][3] += MemoHorizontalJet->Lines->Strings[j][i] - '0';
                                        imageFeatures[2][3] += MemoDiagonalJet->Lines->Strings[j][i] - '0';
                                }

                                else if (i>=width/3 && i<2*(width/3))
                                {
                                        imageFeaturesOld[0][4] += MemoVerticalPost->Lines->Strings[j][i] - '0';
                                        imageFeaturesOld[1][4] += MemoHorizontalPost->Lines->Strings[j][i] - '0';
                                        imageFeaturesOld[2][4] += MemoDiagonalPost->Lines->Strings[j][i] - '0';

                                        imageFeatures[0][4] += MemoVerticalJet->Lines->Strings[j][i] - '0';
                                        imageFeatures[1][4] += MemoHorizontalJet->Lines->Strings[j][i] - '0';
                                        imageFeatures[2][4] += MemoDiagonalJet->Lines->Strings[j][i] - '0';
                                }

                                else
                                {
                                        imageFeaturesOld[0][5] += MemoVerticalPost->Lines->Strings[j][i] - '0';
                                        imageFeaturesOld[1][5] += MemoHorizontalPost->Lines->Strings[j][i] - '0';
                                        imageFeaturesOld[2][5] += MemoDiagonalPost->Lines->Strings[j][i] - '0';

                                        imageFeatures[0][5] += MemoVerticalJet->Lines->Strings[j][i] - '0';
                                        imageFeatures[1][5] += MemoHorizontalJet->Lines->Strings[j][i] - '0';
                                        imageFeatures[2][5] += MemoDiagonalJet->Lines->Strings[j][i] - '0';
                                }
                        }
                }

                else
                {
                        for(i=1; i<=width-3; i++)
                        {
                                if (i<width/3)
                                {
                                        imageFeaturesOld[0][6] += MemoVerticalPost->Lines->Strings[j][i] - '0';
                                        imageFeaturesOld[1][6] += MemoHorizontalPost->Lines->Strings[j][i] - '0';
                                        imageFeaturesOld[2][6] += MemoDiagonalPost->Lines->Strings[j][i] - '0';

                                        imageFeatures[0][6] += MemoVerticalJet->Lines->Strings[j][i] - '0';
                                        imageFeatures[1][6] += MemoHorizontalJet->Lines->Strings[j][i] - '0';
                                        imageFeatures[2][6] += MemoDiagonalJet->Lines->Strings[j][i] - '0';
                                }

                                else if (i>=width/3 && i<2*(width/3))
                                {
                                        imageFeaturesOld[0][7] += MemoVerticalPost->Lines->Strings[j][i] - '0';
                                        imageFeaturesOld[1][7] += MemoHorizontalPost->Lines->Strings[j][i] - '0';
                                        imageFeaturesOld[2][7] += MemoDiagonalPost->Lines->Strings[j][i] - '0';

                                        imageFeatures[0][7] += MemoVerticalJet->Lines->Strings[j][i] - '0';
                                        imageFeatures[1][7] += MemoHorizontalJet->Lines->Strings[j][i] - '0';
                                        imageFeatures[2][7] += MemoDiagonalJet->Lines->Strings[j][i] - '0';
                                }

                                else
                                {
                                        imageFeaturesOld[0][8] += MemoVerticalPost->Lines->Strings[j][i] - '0';
                                        imageFeaturesOld[1][8] += MemoHorizontalPost->Lines->Strings[j][i] - '0';
                                        imageFeaturesOld[2][8] += MemoDiagonalPost->Lines->Strings[j][i] - '0';

                                        imageFeatures[0][8] += MemoVerticalJet->Lines->Strings[j][i] - '0';
                                        imageFeatures[1][8] += MemoHorizontalJet->Lines->Strings[j][i] - '0';
                                        imageFeatures[2][8] += MemoDiagonalJet->Lines->Strings[j][i] - '0';
                                }
                        }
                }
                ProgressBar1->Position=(j+1)*width;
        }

        //ShowMessage("Stage 6 - Image Jet complete");

        // Save Jet
        rowsize = (height/3.0)*width;
        columnsize = height*(width/3.0);
        boxsize =  (height/3.0)*(width/3.0);

        for (int k=0; k<3; k++)
        {
                float sum,value;

                sum = imageFeaturesOld[k][0];
                sum += imageFeaturesOld[k][3];
                sum += imageFeaturesOld[k][6];

                MemoJet->Lines->Add(sum/columnsize);

                sum = imageFeaturesOld[k][1];
                sum += imageFeaturesOld[k][4];
                sum += imageFeaturesOld[k][7];

                MemoJet->Lines->Add(sum/columnsize);

                sum = imageFeaturesOld[k][2];
                sum += imageFeaturesOld[k][5];
                sum += imageFeaturesOld[k][8];

                MemoJet->Lines->Add(sum/columnsize);

                sum = imageFeaturesOld[k][0];
                sum += imageFeaturesOld[k][1];
                sum += imageFeaturesOld[k][2];

                MemoJet->Lines->Add(sum/rowsize);

                sum = imageFeaturesOld[k][3];
                sum += imageFeaturesOld[k][4];
                sum += imageFeaturesOld[k][5];

                MemoJet->Lines->Add(sum/rowsize);

                sum = imageFeaturesOld[k][6];
                sum += imageFeaturesOld[k][7];
                sum += imageFeaturesOld[k][8];

                MemoJet->Lines->Add(sum/rowsize);

                for (int l=0; l<9; l++)
                        MemoJet->Lines->Add(imageFeaturesOld[k][l]/boxsize);
        }

        for (int k=0; k<3; k++)
        {
                float sum,value;

                sum = imageFeatures[k][0];
                sum += imageFeatures[k][3];
                sum += imageFeatures[k][6];

                MemoJet->Lines->Add(sum/columnsize);

                sum = imageFeatures[k][1];
                sum += imageFeatures[k][4];
                sum += imageFeatures[k][7];

                MemoJet->Lines->Add(sum/columnsize);

                sum = imageFeatures[k][2];
                sum += imageFeatures[k][5];
                sum += imageFeatures[k][8];

                MemoJet->Lines->Add(sum/columnsize);

                sum = imageFeatures[k][0];
                sum += imageFeatures[k][1];
                sum += imageFeatures[k][2];

                MemoJet->Lines->Add(sum/rowsize);

                sum = imageFeatures[k][3];
                sum += imageFeatures[k][4];
                sum += imageFeatures[k][5];

                MemoJet->Lines->Add(sum/rowsize);

                sum = imageFeatures[k][6];
                sum += imageFeatures[k][7];
                sum += imageFeatures[k][8];

                MemoJet->Lines->Add(sum/rowsize);

                for (int l=0; l<9; l++)
                        MemoJet->Lines->Add(imageFeatures[k][l]/boxsize);
        }

        //ShowMessage("Analysis Complete");

}
//---------------------------------------------------------------------------

void __fastcall TForm1::BitBtn3Click(TObject *Sender)
{
        ShowMessage("1. Creae objects\n2. Select the Noise analysis\n3. Press Analyze");
}

void __fastcall TForm1::Button3Click(TObject *Sender)
{
        ShowMessage("1. Creae objects\n2. Select the Noise analysis\n3. Press Analyze");
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button1Click(TObject *Sender)
{
        OpenDialog1->Filter = "BMP Files|*.bmp";
        OpenDialog1->Execute();
        if (OpenDialog1->FileName.Length()>4)
        {
                Image1->Picture->LoadFromFile(OpenDialog1->FileName);
                ImageGray->Picture->LoadFromFile(OpenDialog1->FileName);
                ImageComplete->Picture->LoadFromFile(OpenDialog1->FileName);

                Image->Picture->LoadFromFile(OpenDialog1->FileName);
                ImagePost->Picture->LoadFromFile(OpenDialog1->FileName);

        }
        else ShowMessage("Please select a proper filename");
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button4Click(TObject *Sender)
{

        int i;

        for(i=1;i<=15;i++)
        {
                MemoJet->Lines->Clear();
                char FileName[200],JetName[200];
                sprintf(FileName,"C:\\Documents and Settings\\Administrator\\Desktop\\Prometheus\\Images\\Rooms\\sample_image_%d\\sample_image_%dg.bmp",i,i);
                sprintf(JetName,"C:\\Documents and Settings\\Administrator\\Desktop\\Prometheus\\Images\\Rooms\\sample_image_%d\\Jet.txt",i,i);

                Image1->Picture->LoadFromFile(FileName);
                ImageGray->Picture->LoadFromFile(FileName);
                ImageComplete->Picture->LoadFromFile(FileName);

                Image->Picture->LoadFromFile(FileName);
                ImagePost->Picture->LoadFromFile(FileName);

                BitBtn2Click(Button4);
                MemoJet->Lines->SaveToFile(JetName);

        }

}
//---------------------------------------------------------------------------




