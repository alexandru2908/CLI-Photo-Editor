#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#pragma pack(1)

typedef struct 
{
    unsigned char  fileMarker1; /* 'B' */
    unsigned char  fileMarker2; /* 'M' */
    unsigned int   bfSize; /* File's size */
    unsigned short unused1; /* Aplication specific */
    unsigned short unused2; /* Aplication specific */
    unsigned int   imageDataOffset; /* Offset to the start of image data */
} bmp_fileheader;

typedef struct 
{
    unsigned int   biSize; /* Size of the info header - 40 bytes */
    signed int     width; /* Width of the image */
    signed int     height; /* Height of the image */
    unsigned short planes;
    unsigned short bitPix; /* Number of bits per pixel = 3 * 8 (for each channel R, G, B we need 8 bits */
    unsigned int   biCompression; /* Type of compression */
    unsigned int   biSizeImage; /* Size of the image data */
    int            biXPelsPerMeter;
    int            biYPelsPerMeter;
    unsigned int   biClrUsed;
    unsigned int   biClrImportant;
} bmp_infoheader;

#pragma pack()

typedef struct culori{
     unsigned char b,g,r;
 }Culori;

int main()
{
    char s[50],cale[50],tip[16],*p,tip_set[15],*lit,a;
    int n=1,x,y,x1,y1,x2,y2,x3,y3,width,height,R,G,B,x_set,point,j,i,minw,minh,xmax,ymax,maxline,z,k,l,aux;
    int yline,xline,x_set1,xinceput,xfinal,yinceput,yfinal;
    unsigned int xf,yf;
    Culori **mat,**mat1,culoare;
    short unused;
    //printf("da");
    bmp_fileheader imagine,ins;
    bmp_infoheader imagine1,ins1;
    while(n)
    {
        scanf("%s",s);
        //printf("da");
        if(strcmp(s,"fill")==0)
        {
            scanf("%d %d",&x,&y);
            printf("%d %d\n",x,y);
        }
        if(strcmp(s,"insert")==0)
        {
            scanf("%s%d%d",cale,&xf,&yf);
           // printf("%s %d %d",cale,xf,yf);
            FILE * insert=fopen(cale,"rb");
            a=fread(&ins.fileMarker1,1,1,insert);
            a=fread(&ins.fileMarker2,1,1,insert);
            point=fread(&ins.bfSize,4,1,insert);
            unused=fread(&ins.unused1,2,1,insert);
            unused=fread(&ins.unused2,2,1,insert);
            point=fread(&ins.imageDataOffset,4,1,insert);
            fread(&ins1,sizeof(bmp_infoheader),1,insert);
            mat1=malloc(ins1.height * sizeof(int *) );
            for(i=0;i<ins1.height;i++)
                mat1[i]=calloc(ins1.width , sizeof(Culori) );
            for(i=0;i<ins1.height;i++)
                for(j=0;j<ins1.width;j++)
                    fread(&mat1[i][j],sizeof(Culori),1,insert);
            if(imagine1.width-xf<ins1.width)
            minw=imagine1.width-xf;
            else
            minw=ins1.width;
            if(imagine1.height-yf<ins1.height)
            minh=imagine1.height-yf;
            else
            minh=ins1.height;
            if(imagine1.width>xf && imagine1.height>yf)
            {
                for(i=yf;i<minh+yf;i++)
                for(j=xf;j<minw+xf;j++)
                        mat[i][j]=mat1[i-yf][j-xf];
            }
            fclose(insert);
            
        }
        if(strcmp(s,"set")==0)
            {
                scanf("%s",tip_set);
                if(strcmp(tip_set,"draw_color")==0)
                    {
                        scanf("%d%d%d",&R,&G,&B);
                        culoare.r=R;
                        culoare.g=G;
                        culoare.b=B;
                    }
                else if(strcmp(tip_set,"line_width")==0)
                    scanf("%d",&x_set);
            }
        if(strcmp(s,"draw")==0)
        {
            scanf("%s",tip);
            if(strcmp(tip,"line")==0)
                {
                    scanf("%d%d%d%d",&y1,&x1,&y2,&x2);
                    for(k=x1-(x_set-1)/2;k<=x1+ (x_set-1) /2;k++)
                    for(l=y1- (x_set-1) /2;l<=y1+ (x_set-1) /2;l++)
                        mat[k][l]=culoare;
                    for(k=x2- (x_set-1) /2;k<=x2+ (x_set-1) /2;k++)
                    for(l=y2- (x_set-1)/2;l<=y2+ (x_set-1) /2;l++)
                        mat[k][l]=culoare;
                   /* if(x1==x2)
                    {
                        for(l=y1- (x_set-1) /2;l<=y1+ (x_set-1) /2;l++)
                            mat[x1][l]=culoare;

                    }
                    else
                    if(y1==y2)
                    {
                        for(k=x1-(x_set-1)/2;k<=x1+ (x_set-1) /2;k++)
                            mat[k][y1]=culoare;
                    }*/
                    //else
                   // {
                    xmax=abs(x2-x1);
                    ymax=abs(y2-y1);
                    if(xmax >ymax)
                    {
                        if(x2>x1)
                        {
                            for(i=x1;i<=x2;i++)
                            {
                                yline=( (i-x1)*(y2-y1) +y1*(x2-x1) )/(x2-x1);
                                for( k=i-(x_set)/2;k<=i+(x_set)/2;k++ )
                                    for(l=yline-(x_set) /2; l<=yline+ (x_set) /2;l++)
                                                mat[k][l]=culoare;
                            }
                        }
                        else
                        {
                            for(i=x2;i<=x1;i++)
                            {
                                yline=( (i-x1)*(y2-y1) +y1*(x2-x1) )/(x2-x1);
                                for( k=i-(x_set)/2;k<=i+(x_set)/2;k++ )
                                    for(l=yline-(x_set) /2; l<=yline+ (x_set) /2;l++)
                                                mat[k][l]=culoare;
                            }
                        }
                    }
                    else
                        {
                        if(y2>y1)
                        {
                            for(i=y1;i<=y2;i++)
                        {
                            xline=( (i-y1)*(x2-x1)+ x1*(y2-y1) ) / (y2-y1);
                            for(k=xline-(x_set)/2; k<=xline+(x_set)/2;k++)
                                for(l= i-(x_set)/2; l<= i+(x_set)/2;l++)
                                    mat[k][l]=culoare;
                        }
                        }
                        else
                        {
                            for(i=y2;i<=y1;i++)
                        {
                            xline=( (i-y1)*(x2-x1)+ x1*(y2-y1) ) / (y2-y1);
                            for(k=xline-(x_set)/2; k<=xline+(x_set)/2;k++)
                                for(l= i-(x_set)/2; l<= i+(x_set)/2;l++)
                                    mat[k][l]=culoare;
                        }
                        }
                        
                        }
                    //}
                }
            else if(strcmp(tip,"rectangle")==0)
                {
                    scanf("%d%d%d%d",&y1,&x1,&width,&height);
                   for(i=y1-x_set/2;i<=y1+width+x_set/2;i++)
                        {                   
                            k=0;
                              while(k<x_set/2+1)
                                {
                                    mat[x1+k][i]=culoare;
                                    mat[x1+height+k][i]=culoare;  
                                    mat[x1-k][i]=culoare;
                                    mat[x1+height-k][i]=culoare; 
                                    k++;
                                }
                        }
                   for(i=x1-x_set/2;i<=x1+height+x_set/2;i++)
                        {
                            k=0;
                              while(k<x_set/2+1)
                                {
                                    mat[i][y1+k]=culoare;
                                    mat[i][y1+width+k]=culoare;
                                    mat[i][y1-k]=culoare;
                                    mat[i][y1+width-k]=culoare; 
                                    k++;
                                }
                        }
                }
            else if(strcmp(tip,"triangle")==0)
                {
                    scanf("%d%d%d%d%d%d",&y1,&x1,&y2,&x2,&y3,&x3);
                    for(k=x1-(x_set-1)/2;k<=x1+ (x_set-1) /2;k++)
                    for(l=y1- (x_set-1) /2;l<=y1+ (x_set-1) /2;l++)
                        {
                            if( (k>=0 && k<=imagine1.height) && (l>=0 && l<=imagine1.width))
                            mat[k][l]=culoare;
                        }
                    for(k=x2- (x_set-1) /2;k<=x2+ (x_set-1) /2;k++)
                    for(l=y2- (x_set-1)/2;l<=y2+ (x_set-1) /2;l++)
                        {
                            if( (k>=0 && k<=imagine1.height) && (l>=0 && l<=imagine1.width))
                            mat[k][l]=culoare;
                        }
                    for(k=x3- (x_set-1) /2;k<=x3+ (x_set-1) /2;k++)
                    for(l=y3- (x_set-1)/2;l<=y3+ (x_set-1) /2;l++)
                        {
                            if( (k>=0 && k<=imagine1.height) && (l>=0 && l<=imagine1.width))
                            mat[k][l]=culoare;
                        }
                    xmax=abs(x2-x1);
                    ymax=abs(y2-y1);
                    if(xmax >ymax)
                    {
                        if(x2>x1)
                        {
                            for(i=x1;i<=x2;i++)
                            {
                                yline=( (i-x1)*(y2-y1) +y1*(x2-x1) )/(x2-x1);
                                for( k=i-(x_set)/2;k<=i+(x_set)/2;k++ )
                                    for(l=yline-(x_set) /2; l<=yline+ (x_set) /2;l++)
                                                {
                                         if( (k>=0 && k<=imagine1.height) && (l>=0 && l<=imagine1.width))
                                         mat[k][l]=culoare;
                                                }
                            }
                        }
                        else
                        {
                            for(i=x2;i<=x1;i++)
                            {
                                yline=( (i-x1)*(y2-y1) +y1*(x2-x1) )/(x2-x1);
                                for( k=i-(x_set)/2;k<=i+(x_set)/2;k++ )
                                    for(l=yline-(x_set) /2; l<=yline+ (x_set) /2;l++)
                                                {
                                        if( (k>=0 && k<=imagine1.height) && (l>=0 && l<=imagine1.width))
                                        mat[k][l]=culoare;
                                                 }
                            }
                        }
                    }
                    else
                        {
                        if(y2>y1)
                        {
                            for(i=y1;i<=y2;i++)
                        {
                            xline=( (i-y1)*(x2-x1)+ x1*(y2-y1) ) / (y2-y1);
                            for(k=xline-(x_set)/2; k<=xline+(x_set)/2;k++)
                                for(l= i-(x_set)/2; l<= i+(x_set)/2;l++)
                                            {
                                                 if( (k>=0 && k<=imagine1.height) && (l>=0 && l<=imagine1.width))
                                                mat[k][l]=culoare;
                                             }
                        }
                        }
                        else
                        {
                            for(i=y2;i<=y1;i++)
                        {
                            xline=( (i-y1)*(x2-x1)+ x1*(y2-y1) ) / (y2-y1);
                            for(k=xline-(x_set)/2; k<=xline+(x_set)/2;k++)
                                for(l= i-(x_set)/2; l<= i+(x_set)/2;l++)
                                    {
                                        if( (k>=0 && k<=imagine1.height) && (l>=0 && l<=imagine1.width))
                                        mat[k][l]=culoare;
                                     }
                        }
                        }
                        
                        }

                    xmax=abs(x3-x1);
                    ymax=abs(y3-y1);
                    if(xmax >ymax)
                    {
                        if(x3>x1)
                        {
                            for(i=x1;i<=x3;i++)
                            {
                                yline=( (i-x1)*(y3-y1) +y1*(x3-x1) )/(x3-x1);
                                for( k=i-(x_set)/2;k<=i+(x_set)/2;k++ )
                                    for(l=yline-(x_set) /2; l<=yline+ (x_set) /2;l++)
                                                {
                                         if( (k>=0 && k<=imagine1.height) && (l>=0 && l<=imagine1.width))
                                         mat[k][l]=culoare;
                                                }
                            }
                        }
                        else
                        {
                            for(i=x3;i<=x1;i++)
                            {
                                yline=( (i-x1)*(y3-y1) +y1*(x3-x1) )/(x3-x1);
                                for( k=i-(x_set)/2;k<=i+(x_set)/2;k++ )
                                    for(l=yline-(x_set) /2; l<=yline+ (x_set) /2;l++)
                                                {
                                        if( (k>=0 && k<=imagine1.height) && (l>=0 && l<=imagine1.width))
                                        mat[k][l]=culoare;
                                                 }
                            }
                        }
                    }
                    else
                        {
                        if(y3>y1)
                        {
                            for(i=y1;i<=y3;i++)
                        {
                            xline=( (i-y1)*(x3-x1)+ x1*(y3-y1) ) / (y3-y1);
                            for(k=xline-(x_set)/2; k<=xline+(x_set)/2;k++)
                                for(l= i-(x_set)/2; l<= i+(x_set)/2;l++)
                                            {
                                                 if( (k>=0 && k<=imagine1.height) && (l>=0 && l<=imagine1.width))
                                                mat[k][l]=culoare;
                                             }
                        }
                        }
                        else
                        {
                            for(i=y3;i<=y1;i++)
                        {
                            xline=( (i-y1)*(x3-x1)+ x1*(y3-y1) ) / (y3-y1);
                            for(k=xline-(x_set)/2; k<=xline+(x_set)/2;k++)
                                for(l= i-(x_set)/2; l<= i+(x_set)/2;l++)
                                    {
                                        if( (k>=0 && k<=imagine1.height) && (l>=0 && l<=imagine1.width))
                                        mat[k][l]=culoare;
                                     }
                        }
                        }
                        
                    }

                    						        xmax=abs(x3-x2);
                    ymax=abs(y3-y2);
                    if(xmax >ymax)
                    {
                        if(x3>x1)
                        {
                            for(i=x1;i<=x3;i++)
                            {
                                yline=( (i-x2)*(y3-y2) +y2*(x3-x2) )/(x3-x2);
                                for( k=i-(x_set)/2;k<=i+(x_set)/2;k++ )
                                    for(l=yline-(x_set) /2; l<=yline+ (x_set) /2;l++)
                                                {
                                         if( (k>=0 && k<=imagine1.height) && (l>=0 && l<=imagine1.width))
                                         mat[k][l]=culoare;
                                                }
                            }
                        }
                        else
                        {
                            for(i=x3;i<=x2;i++)
                            {
                                yline=( (i-x2)*(y3-y2) +y2*(x3-x2) )/(x3-x2);
                                for( k=i-(x_set)/2;k<=i+(x_set)/2;k++ )
                                    for(l=yline-(x_set) /2; l<=yline+ (x_set) /2;l++)
                                                {
                                        if( (k>=0 && k<=imagine1.height) && (l>=0 && l<=imagine1.width))
                                        mat[k][l]=culoare;
                                                 }
                            }
                        }
                    }
                    else
                        {
                        if(y3>y2)
                        {
                            for(i=y2;i<=y3;i++)
                        {
                            xline=( (i-y2)*(x3-x2)+ x1*(y3-y2) ) / (y3-y2);
                            for(k=xline-(x_set)/2; k<=xline+(x_set)/2;k++)
                                for(l= i-(x_set)/2; l<= i+(x_set)/2;l++)
                                            {
                                                 if( (k>=0 && k<=imagine1.height) && (l>=0 && l<=imagine1.width))
                                                mat[k][l]=culoare;
                                             }
                        }
                        }
                        else
                        {
                            for(i=y3;i<=y2;i++)
                        {
                            xline=( (i-y2)*(x3-x2)+ x2*(y3-y2) ) / (y3-y2);
                            for(k=xline-(x_set)/2; k<=xline+(x_set)/2;k++)
                                for(l= i-(x_set)/2; l<= i+(x_set)/2;l++)
                                    {
                                        if( (k>=0 && k<=imagine1.height) && (l>=0 && l<=imagine1.width))
                                        mat[k][l]=culoare;
                                     }
                        }
                        }
                        
                        }
                    
                }
           
        }
        if(strcmp(s,"save")==0)
        {
            scanf("%s",cale);
            FILE *imag1=fopen(cale,"wb");
            fwrite(&imagine,sizeof(bmp_fileheader),1,imag1);
            fwrite(&imagine1,sizeof(bmp_infoheader),1,imag1);
            for(i=0;i<imagine1.height;i++)
                for(j=0;j<imagine1.width;j++)
                    fwrite(&mat[i][j],sizeof(Culori),1,imag1);
            fclose(imag1);
        }
        if(strcmp(s,"edit")==0)
        {
            scanf("%s",cale);
            FILE *imag=fopen(cale,"rb");
            fread(&imagine,sizeof(bmp_fileheader),1,imag);
            fread(&imagine1,sizeof(bmp_infoheader),1,imag);
            mat=malloc(imagine1.height * sizeof(int *) );
            for(i=0;i<imagine1.height;i++)
                mat[i]=calloc(imagine1.width , sizeof(Culori) );
            for(i=0;i<imagine1.height;i++)
                for(j=0;j<imagine1.width;j++)
                    fread(&mat[i][j],sizeof(Culori),1,imag);
            fclose(imag);
        }
        if(strcmp(s,"quit")==0)
        {
            n=0;
            break;
        }
   }
}