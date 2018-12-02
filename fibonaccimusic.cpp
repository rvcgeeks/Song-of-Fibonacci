/*
 * The Song of fibonacci sequence by #rvcgeeks 
 * one of my masterpieces in Music and coding... ;)
 * created on 30 Aug 2018,Pune
 * for more geeks mailto rvchavadekar@gmail.com
 * 
 * dependencies -- midimake.cpp (main removed)-- wrapper class to create midi files
 *                 thanks to channel Bisqwit (youtube) 
 *                 taken from video https://youtu.be/6PFf6klllAE
 * 
 * inspired by --  The Eternal Music - decoded from the Fibonacci Sequence 
 *                 by channel Radomir Nowotarski on youtube
 *                 https://youtu.be/SRTViZ2NPpY
 */

#include "midimake.cpp"

int fib(int n)             //function to actually calculate the fibonacci sequence
{
    return n==0?0:(n==1?1:fib(n-1)+fib(n-2));
}
int lydian(int n)          //to write the lydian scale in midi format
{
    start:switch(n)
    {                      //octave/note 
        case 0:return -3;  //-2/A
        case 1:return -1;  //-2/B        //tonic octaves
        
        case 2:return 0;   //-1/C
        case 3:return 2;   //-1/D
        case 4:return 4;   //-1/E
        case 5:return 6;   //-1/F#
        case 6:return 7;   //-1/G
        case 7:return 9;   //-1/A
        case 8:return 11;  //-1/B
        
        case 9:return 12;  // 0/C
        
        default:n=n-7;goto start;      //et cetera calculation jump
    }
}
int lydchord(int n,int i)  //extracting chords from lydian scale
{
    switch(n)
    {
        case -3:switch(i)  //chord vi previous
        {
        case 0:return -3; //-2/A
        case 1:return 0;  //-1/C
        case 2:return 4;  //-1/E
        }
        case -1:switch(i)  //chord vii previous
        {
        case 0:return -1;  //-2/B
        case 1:return 2;   //-1/D
        case 2:return 6;   //-1/F#
        }
            
        case 0:switch(i)    //chord I
        {
        case 0:return 0;    //-1/C
        case 1:return 4;    //-1/E
        case 2:return 7;    //-1/G
        }
        case 2:switch(i)    //chord II
        {
        case 0:return 2;    //-1/D
        case 1:return 6;    //-1/F#
        case 2:return 9;    //-1/A
        }
        case 4:switch(i)    //chord iii
        {
        case 0:return 4;    //-1/E
        case 1:return 7;    //-1/G
        case 2:return 11;   //-1/B
        }
        case 6:switch(i)    //chord iv o
        {
        case 0:return 6;    //-1/F#
        case 1:return 9;    //-1/A
        case 2:return 12;   //0/C
        }
        case 7:switch(i)    //chord V
        {
        case 0:return 7;    //-1/G
        case 1:return 11;   //-1/B
        case 2:return 14;   //0/D
        }
        case 9:switch(i)    //chord vi
        {
        case 0:return 9;    //-1/A
        case 1:return 12;   //0/C
        case 2:return 16;   //0/E
        }
        case 11:switch(i)   //chord vii
        {
        case 0:return 11;   //-1/B
        case 1:return 14;   //0/D
        case 2:return 18;   //0/F#
        }
            
        case 12:switch(i)   //chord I next
        {
        case 0:return 12;   //0/C
        case 1:return 16;   //0/E
        case 2:return 19;   //0/G
        }
        default:return n;
    }
}
main()
{
    
    const char x = 99; // Arbitrary value we use here to indicate "no note"
    static const char chordline[64] =                                          //umm maybe i kept this for future expansion... ;)
    {
        x,x,x,x,x,x,x, x,x,x,x,x,x,x,x,x,  x,x,x,x,x,x,x, x,x,x,x,x,x,x,x,x,
        x,x,x,x,x,x,x, x,x,x,x,x,x,x,x,x,  x,x,x,x,x,x,x,x,x,x,x,x,x,x,x,x
    };
    static const char bassline[64] =
    {
        x,x,x,x,x,x,x, x,x,x,x,x,x,x,x,x,  x,x,x,x,x,x,x, x,x,x,x,x,x,x,x,x,
        x,x,x,x,x,x,x, x,x,x,x,x,x,x,x,x,  x,x,x,x,x,x,x, x,x,x,x,x,x,x,x,x
    };
    
    char fluteline[64]; 
    int u,i;
    
    for(i=0;i<32;i++)        
    {
        u=lydian(1+fib(i+1)); //actual calculation of fibonacci sequence and extracting flute notes in lydian scale
        fluteline[i]=u;
        fluteline[32+i]=u;
    }
    
    
    fluteline[13]=-3;         // by remainder calculation to convert et cetera of lydian to tonic octaves
    fluteline[32+13]=-3;      // the unnecessary higher notes are produced
                              // hence we bring them back to the tonic scale explicitly 
    fluteline[14]=0;          // as they have the same integer notation
    fluteline[32+14]=0;       // in the extended lydian scale so ultimately we arent 
                              // disturbing the original fibonacci sequence 
    fluteline[15]=-1;         // this is all done for artistic effects and to produce a harmony...
    fluteline[32+15]=-1;
    
    fluteline[16]=0;
    fluteline[32+16]=0;
    
    fluteline[17]=0;
    fluteline[32+17]=0;
    
    fluteline[29]=-3;
    fluteline[32+29]=-3;
    
    fluteline[30]=0;
    fluteline[32+30]=0;
    
    fluteline[31]=-1;
    fluteline[32+31]=-1;
    
    char chordline2[64];
    
    for(i=0;i<32;i++)         // setting up the chords at half the metrotome 
    {
        chordline2[2*i]=fluteline[i];
        chordline2[2*i+1]=x;
    }
    
    MIDIfile file;
    file.AddLoopStart();
    
    /* Choose instruments ("patches") for each channel: */
    static const char patches[16] =
    {
        0,0, 52,52,52, 48,48,48,48, 0,0,0,0,0, 35,74
        /* 0=piano, 52=choir aahs, 48=strings, 35=fretless bass, 74=pan flute */
    };
    for(unsigned c=0; c<16; ++c)
        if(c != 10) // Patch any other channel but not the percussion channel.
            file[0].Patch(c, patches[c]);
    
    int keys_on[16] = {-1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,-1 };
    for(unsigned loops=0; loops<1; ++loops)
    {
        for(unsigned row=0; row<128; ++row)
        {
            for(unsigned c=0; c<16; ++c)
            {
                int note = x, add = 0, vol = 127;
                if(c < 2) // Piano chord
                  { int chord = chordline[row%64];
                    if(1/*chord != x*/) note = lydchord(chord,c%3), add=12*5, vol=0x4B; }
                else if(c >= 2 && c < 5 && row >= 16) // Aux chord (choir)
                  { int chord = chordline2[row%64];
                    note = lydchord(chord,c%3), add=12*4, vol=row<32?0x30+2*(row-16):0x50; }
                else if(c >= 5 && c < 8 && row >= 32) // Aux chord (strings)
                  { int chord = chordline2[row%64];
                    note = lydchord(chord,c%3), add=12*5, vol=row<48?0x25+(row-32):0x35; }
                else if(c == 14) // Bass
                    note = bassline[row%64], add=12*3, vol=0x6F;
                else if(c == 15/* && row >= 64*/) // Flute
                    note = fluteline[row%64], add=12*5, vol=row>=32?(row>=48?0x40:0x60):0x7F;
                if(note == x && (c<15 || row%31)) continue;
                file[0].KeyOff(c, keys_on[c], 0x20);
                keys_on[c] = -1;
                if(note == x) continue;
                file[0].KeyOn(c, keys_on[c] = note+add, vol);
            }
            file[0].AddDelay(800);
        }
        if(loops == 0) file.AddLoopEnd();
    }
    
    file.Finish();
    
    FILE* fp = std::fopen("fibonaccisong.mid", "wb");          
    std::fwrite(&file.at(0), 1, file.size(), fp);            //write the midi file finally
    std::fclose(fp);                                         //all done here ... u may use timidity to play this on linux
    
    return 0;
}