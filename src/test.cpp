 //
//  test.cpp
//  libRealSpace
//
//  Created by Fabien Sanglard on 12/28/2013.
//  Copyright (c) 2013 Fabien Sanglard. All rights reserved.
//

#include "precomp.h"



void testTRE(void){
    
    TreArchive treArchive;
    treArchive.InitFromFile("OBJECTS.TRE");
    treArchive.List(stdout);
    
}





//const char* trePath = "OBJECTS.TRE";
//const char* jetPath = "..\\..\\DATA\\OBJECTS\\F-16DES.IFF";
void testShowAllJetTextures(const char* trePath,const char* jetPath)
{
    
    renderer.Init(2);
    
    // Let's open the TRE archive.
    TreArchive treArchive;
    treArchive.InitFromFile(trePath);
    //treArchive.List(stdout);
    
    // Let's open the jet IFF file in that archive
    TreEntry* iffJet = treArchive.GetEntryByName(jetPath);
    
    // Oops !
    if (iffJet == NULL){
        printf("Unable to find jet '%s' in TRE archive '%s'.\n",jetPath,trePath);
        return;
    }
    
    
    
    
    
    IffLexer jetIffLexer;
    jetIffLexer.InitFromRAM(iffJet->data,iffJet->size);
    
    //Verify the object has an appearance
    if (jetIffLexer.GetChunkByID('APPR') != NULL){
        ;//printf("This object does have an appearance.\n");
    }
    else{
        printf("This object does NOT have an appearance !!\n");
        return;
    }
    
    //Render it !
    renderer.SetTitle(jetPath);
    
    
    RSEntity jet;
    jet.InitFromIFF(&jetIffLexer);
    
    printf("Model '%s' features %lu textures.\n",jetPath,jet.NumImages());
    for(size_t i = 0 ; i < jet.NumImages(); i++){
        RSImage* image = jet.images[i];
        renderer.DrawImage(image,2);
        renderer.Swap();
    }
        
}

void ShowAllJets(void){
    
    renderer.Init(4);
    
    const char* trePath = "OBJECTS.TRE";
    
    // Let's open the TRE archive.
    TreArchive treArchive;
    treArchive.InitFromFile(trePath);
    
    for (size_t i = 0 ; i < treArchive.GetNumEntries(); i++) {
        

        
        TreEntry* e = treArchive.GetEntryByID(i);

        printf("Rendering jet [%lu] '%s'.\n",i,e->name);
        
        IffLexer lexer;
        lexer.InitFromRAM(e->data,e->size);
        
        if (lexer.GetChunkByID('APPR') == NULL){
            continue;
            printf("Skipping '%s' (No APPR).\n",e->name);
        }
        
        //Render it !
        renderer.SetTitle(e->name);
        
        
        RSEntity jet;
        jet.InitFromIFF(&lexer);
        
        //Oops we don't have that number of level
        if (jet.NumLods() <= LOD_LEVEL_MAX ){
            printf("Skipping '%s' (No LOD_LEVEL_MAX).\n",e->name);
            continue;
        }

        
        
        renderer.DisplayModel(&jet,LOD_LEVEL_MAX);
    }
}

void testJet(void){
    
    const char* trePath = "OBJECTS.TRE";
    //const char* jetPath = "..\\..\\DATA\\OBJECTS\\A-10.IFF";
    //const char* jetPath = "..\\..\\DATA\\OBJECTS\\EJECSEAT.IFF";
    const char* jetPath = "..\\..\\DATA\\OBJECTS\\F-16DES.IFF";
    //const char* jetPath = "..\\..\\DATA\\OBJECTS\\MIRAGE.IFF";
    //const char* jetPath = "..\\..\\DATA\\OBJECTS\\F-22.IFF";
    //const char* jetPath = "..\\..\\DATA\\OBJECTS\\F-15.IFF";
    //const char* jetPath = "..\\..\\DATA\\OBJECTS\\YF23.IFF";
    //const char* jetPath = "..\\..\\DATA\\OBJECTS\\MIG21.IFF";
    //const char* jetPath = "..\\..\\DATA\\OBJECTS\\MIG29.IFF";
    //const char* jetPath = "..\\..\\DATA\\OBJECTS\\SU27.IFF";
    
    
    // Let's open the TRE archive.
    TreArchive treArchive;
    treArchive.InitFromFile(trePath);
    treArchive.List(stdout);
    
    // Let's open the jet IFF file in that archive
    TreEntry* iffJet = treArchive.GetEntryByName(jetPath);
    
    // Oops !
    if (iffJet == NULL){
        printf("Unable to find jet '%s' in TRE archive '%s'.\n",jetPath,trePath);
        return;
    }
        
    
    
    

    IffLexer jetIffLexer;
    jetIffLexer.InitFromRAM(iffJet->data,iffJet->size);
    
    //Verify the object has an appearance
    if (jetIffLexer.GetChunkByID('APPR') != NULL){
        ;//printf("This object does have an appearance.\n");
    }
    else{
        printf("This object does NOT have an appearance !!\n");
        return;
    }
    
    //Render it !
    renderer.SetTitle(jetPath);
    
    
    RSEntity jet;
    jet.InitFromIFF(&jetIffLexer);
    renderer.DisplayModel(&jet,LOD_LEVEL_MAX);
     
}

void testPalette(void){
    
    IffLexer lexer ;
    lexer.InitFromFile("PALETTE.IFF");
    lexer.List(stdout);
    
    RSPalette palette;
    palette.InitFromIFF(&lexer);
}

void testTREDecompress(const char* dst){
    
   // const char* trePath = "GAMEFLOW.TRE";
   // const char* trePath = "MISC.TRE";
   // const char* trePath = "MISSIONS.TRE";
   // const char* trePath = "OBJECTS.TRE";
   // const char* trePath = "SOUND.TRE";
    const char* trePath = "TEXTURES.TRE";
   
    
    TreArchive treArchive;
    treArchive.InitFromFile(trePath);
    treArchive.Decompress(dst);
}

void testPAKDecompress(void){
    
    const char* trePath = "GAMEFLOW.TRE";
    TreArchive treArchive;
    treArchive.InitFromFile(trePath);
    
    treArchive.List(stdout);
    
    //Find the sounds PAKS.
    const char* pakName = "..\\..\\DATA\\MIDGAMES\\MID1VOC.PAK";
    TreEntry* treEntry = treArchive.GetEntryByName(pakName);
    
    
    PakArchive pakArchive;
    pakArchive.InitFromRAM(pakName,treEntry->data, treEntry->size);
    
    //Decompress it
    pakArchive.Decompress(".","VOC");
}

void testShowAllTexturesPAK(void){
    
    renderer.Init(2);
    
    const char* trePath = "TEXTURES.TRE";
    TreArchive treArchive;
    treArchive.InitFromFile(trePath);
    
    //Find the texture PAKS.
    TreEntry* treEntry = NULL;
    const char* pakName = "..\\..\\DATA\\TXM\\TXMPACK.PAK";
    treEntry = treArchive.GetEntryByName(pakName);
    
    PakArchive txmPakArchive;
    txmPakArchive.InitFromRAM(pakName,treEntry->data, treEntry->size);
   // txmPakArchive.Decompress("/Users/fabiensanglard/Desktop/DATA/", ".TXT");
    
    RSMapTextureSet txmTextureSet ;
    txmTextureSet.InitFromPAK(&txmPakArchive);
    txmTextureSet.List(stdout);
    
    
    renderer.ShowWindow();
    renderer.SetTitle("TXMPACK.PAK");
    
    //Show all textures
    for(size_t i=0 ; i < txmTextureSet.GetNumImages() ; i++ ){
        printf("Drawing %lu.\n",i);
        RSImage* image = txmTextureSet.GetImageById(i);
        renderer.Clear();
        renderer.DrawImage(image,4);
        renderer.Swap();
        renderer.Pause();
        while (renderer.IsPaused()) {
            renderer.PumpEvents();
        }
    }
    
    
    
    
    const char* accPakName = "..\\..\\DATA\\TXM\\ACCPACK.PAK";
    treEntry = treArchive.GetEntryByName(accPakName);
    
    PakArchive accPakArchive;
    accPakArchive.InitFromRAM(accPakName,treEntry->data, treEntry->size);
    //accPakArchive.List(stdout);
    
        renderer.SetTitle("ACCPACK.PAK");
    
    //Show all textures
    RSMapTextureSet accTextureSet ;
    accTextureSet.InitFromPAK(&accPakArchive);
    //Show all textures
    for(size_t i=0 ; i < accTextureSet.GetNumImages() ; i++ ){
        printf("Drawing %lu.\n",i);
        RSImage* image = accTextureSet.GetImageById(i);
        renderer.Clear();
        renderer.DrawImage(image,4);
        renderer.Swap();
        renderer.Pause();
        while (renderer.IsPaused()) {
            renderer.PumpEvents();
        }
    }
}

void testParsePAK(){
    PakArchive archive;
    archive.InitFromFile("MAURITAN.PAK");
    
    archive.List(stdout);
}

int testShowPalette(void)
{
    
    IffLexer lexer ;
    lexer.InitFromFile("PALETTE.IFF");
    lexer.List(stdout);
    
    RSPalette palette;
    palette.InitFromIFF(&lexer);
    VGAPalette* vgaPalette = palette.GetColorPalette();
    
    
    renderer.SetTitle(lexer.GetName());
    
    renderer.ShowPalette(vgaPalette);
    
    return 0;
}


void DecompressAllTRE(void){
    
    TreArchive gameflow ;
    gameflow.InitFromFile("GAMEFLOW.TRE");
    gameflow.List(stdout);
    gameflow.Decompress("/Users/fabiensanglard/Desktop/");
    
    TreArchive misc ;
    misc.InitFromFile("MISC.TRE");
    misc.List(stdout);
    misc.Decompress("/Users/fabiensanglard/Desktop/");
    
    
    TreArchive missions ;
    missions.InitFromFile("MISSIONS.TRE");
    missions.List(stdout);
    missions.Decompress("/Users/fabiensanglard/Desktop/");
    
    
    TreArchive objects ;
    objects.InitFromFile("OBJECTS.TRE");
    objects.List(stdout);
    objects.Decompress("/Users/fabiensanglard/Desktop/");
    
    
    TreArchive sound ;
    sound.InitFromFile("SOUND.TRE");
    sound.List(stdout);
    sound.Decompress("/Users/fabiensanglard/Desktop/");

    TreArchive textures ;
    textures.InitFromFile("TEXTURES.TRE");
    textures.List(stdout);
    textures.Decompress("/Users/fabiensanglard/Desktop/");
}



//DELETE ME
static void showAllImageInArchive(PakArchive* archive){
    
    
    for(size_t i = 0 ; i < archive->GetNumEntries() ; i ++){
        
        printf("Show all images %lu.\n",i);
        PakEntry* entry = archive->GetEntry(i);
        
        
        
        RLECodex codex ;
        size_t byteRead;
        
        RSImage screen;
        screen.Create("SCREEN", 320, 200);
        bool errorFound = codex.ReadImage(entry->data, &screen, &byteRead);
        
        
        renderer.Clear();
        if (!errorFound){
            renderer.Pause();
            while(renderer.IsPaused()){
                
                renderer.DrawImage(&screen, 2);
                renderer.Swap();
                renderer.ShowWindow();
                renderer.PumpEvents();
            }
        }
        screen.ClearContent();
    }
}

void ExploreRootIFFS(void){
    
    //IffLexer instant;
    //instant.InitFromFile("INSTANT.IFF");
    //instant.List(stdout);
    
    IffLexer misn2op;
    misn2op.InitFromFile("MISN2OP.IFF");
    misn2op.List(stdout);
    
    
    IffLexer opt2misn;
    opt2misn.InitFromFile("OP2MISN.IFF");
    opt2misn.List(stdout);
    
    
    IffLexer palette;
    palette.InitFromFile("PALETTE.IFF");
    palette.List(stdout);
    
    
    IffLexer palFade;
    palFade.InitFromFile("PALFADE.IFF");
    palFade.List(stdout);
    
    IffLexer txmList;
    txmList.InitFromFile("TXM_LIST.IFF");
    txmList.List(stdout);
    
    
    
    PakArchive eject;
    eject.InitFromFile("EJECT.PAK");
    eject.List(stdout);
    eject.Decompress("/Users/fabiensanglard/Desktop/DATA/OBJECTS/EJECT/", "TXT");
    
    SetBase("/Users/fabiensanglard/Desktop/DATA/OBJECTS/EJECT/EJECT.PAK.CONTENT");
    
    PakArchive file0;
    file0.InitFromFile("FILE0.TXT");
    file0.List(stdout);
    file0.Decompress("/Users/fabiensanglard/Desktop/DATA/OBJECTS/EJECT/EJECT.PAK.CONTENT/FILE0", "TXT");


    PakArchive file1;
    file1.InitFromFile("FILE1.TXT");
    file1.List(stdout);
    file1.Decompress("/Users/fabiensanglard/Desktop/DATA/OBJECTS/EJECT/EJECT.PAK.CONTENT/FILE1", "TXT");


    PakArchive file2;
    file2.InitFromFile("FILE2.TXT");
    file2.List(stdout);
    file2.Decompress("/Users/fabiensanglard/Desktop/DATA/OBJECTS/EJECT/EJECT.PAK.CONTENT/FILE2", "TXT");
    
    PakArchive file3;
    file3.InitFromFile("FILE3.TXT");
    file3.List(stdout);
    file3.Decompress("/Users/fabiensanglard/Desktop/DATA/OBJECTS/EJECT/EJECT.PAK.CONTENT/FILE3", "TXT");
    
    PakArchive file4;
    file4.InitFromFile("FILE4.TXT");
    file4.List(stdout);
    file4.Decompress("/Users/fabiensanglard/Desktop/DATA/OBJECTS/EJECT/EJECT.PAK.CONTENT/FILE4", "TXT");
    
    PakArchive file5;
    file5.InitFromFile("FILE5.TXT");
    file5.List(stdout);
    file5.Decompress("/Users/fabiensanglard/Desktop/DATA/OBJECTS/EJECT/EJECT.PAK.CONTENT/FILE5", "TXT");
    
    PakArchive file6;
    file6.InitFromFile("FILE6.TXT");
    file6.List(stdout);
    file6.Decompress("/Users/fabiensanglard/Desktop/DATA/OBJECTS/EJECT/EJECT.PAK.CONTENT/FILE6", "TXT");
    
    PakArchive file7;
    file7.InitFromFile("FILE7.TXT");
    file7.List(stdout);
    file7.Decompress("/Users/fabiensanglard/Desktop/DATA/OBJECTS/EJECT/EJECT.PAK.CONTENT/FILE7", "TXT");
    
    PakArchive file8;
    file8.InitFromFile("FILE8.TXT");
    file8.List(stdout);
    file8.Decompress("/Users/fabiensanglard/Desktop/DATA/OBJECTS/EJECT/EJECT.PAK.CONTENT/FILE8", "TXT");
}

void listTRE(void){

    
    TreArchive gameFlow ;
    gameFlow.InitFromFile("GAMEFLOW.TRE");
    gameFlow.List(stdout);

    TreArchive misc ;
    misc.InitFromFile("MISC.TRE");
    misc.List(stdout);

    TreArchive mission ;
    mission.InitFromFile("MISSIONS.TRE");
    mission.List(stdout);
    
    TreArchive objects ;
    objects.InitFromFile("OBJECTS.TRE");
    objects.List(stdout);
    
    TreArchive sound ;
    sound.InitFromFile("SOUND.TRE");
    sound.List(stdout);

    TreArchive textures ;
    textures.InitFromFile("TEXTURES.TRE");
    textures.List(stdout);
    
}

void ShowImage(RSImage* img      ){
    renderer.Pause();
    while(renderer.IsPaused()){
        renderer.Clear();
        renderer.DrawImage(img,2);
        renderer.Swap();
        renderer.PumpEvents();
    }
}

void PrintTabs(int tabs){
    for (size_t i=0 ; i < tabs; i++) {
        printf(" ");
    }
}

void ExploreImages(uint8_t* data, size_t size, int numTabs){
    
    PrintTabs(numTabs);
    printf("Exploring 0X%X\n",data);
    /*
    uint32_t* magic = (uint32_t*)data;
    if (*magic == 'MROF'){
        printf("This is likely a palette.");
    }
    */
    
    //SHP files are PAKs containing direct images.
    PakArchive font;
    font.InitFromRAM("XXXX",data,size);
    if (font.IsReady()){
        PrintTabs(numTabs);
        printf("Pak Found 0X%X\n",data);
        for(size_t i =0 ; i  < font.GetNumEntries() ; i++){
            PakEntry* e = font.GetEntry(i);
            ExploreImages(e->data,e->size,numTabs++);
            
        }
        return;
    }
    
    
    //Myabe it is a direct image ?
    RSImage screen;
    screen.Create("Screen",320, 200);
    RLECodex codex;
    size_t byteRead;
    screen.ClearContent();
    bool error = codex.ReadImage(data, &screen, &byteRead);
    if (!error){
        PrintTabs(numTabs);
        printf("Image Found 0X%X\n",data);
        ShowImage(&screen);
        return;
    }
    
    //TODO there is palette at the end of the sequence of images. It should be retrieved.
    //Maybe it is a sequence of images ?
    uint8_t* end = data + size;
    ByteStream s(data);
    uint32_t nextImage = s.ReadUInt32LE();
    nextImage = nextImage & 0x00FFFFFF;
    
    if (data + nextImage >= end)
        return;
    
    uint32_t numImages = nextImage/4 ;
    for(size_t i = 0 ; i < numImages && (data+nextImage < end) ; i++){
        
        bool error = codex.ReadImage(data+nextImage, &screen, &byteRead);
        if (!error){
            ShowImage(&screen);
            PrintTabs(numTabs);
            printf("Image Found 0X%X\n",data+nextImage);
        }
        
        nextImage = s.ReadUInt32LE();
        nextImage = nextImage & 0x00FFFFFF;
    }
    
}

void TestMouseCursor(void){
    
    renderer.Init(2);

    
    
    /*
    TreArchive misc ;
    misc.InitFromFile("MISC.TRE");
    TreEntry* mainFont = misc.GetEntryByName("..\\..\\DATA\\FONTS\\CAMROPT.SHP"); //Camera configuration
    ExploreImages(mainFont->data,mainFont->size);
*/
    
    /*
     TreArchive misc ;
     misc.InitFromFile("MISC.TRE");
     TreEntry* mainFont = misc.GetEntryByName("..\\..\\DATA\\FONTS\\CHKEXIT.SHP"); //Exit to DOS configuration
     ExploreImages(mainFont->data,mainFont->size);
     */
    
    /*
    TreArchive misc ;
    misc.InitFromFile("MISC.TRE");
    TreEntry* mainFont = misc.GetEntryByName("..\\..\\DATA\\FONTS\\COCKOPT.SHP"); // Cockpit configuration
    ExploreImages(mainFont->data,mainFont->size);
    */
    
    /*
    TreArchive misc ;
    misc.InitFromFile("MISC.TRE");
    TreEntry* mainFont = misc.GetEntryByName("..\\..\\DATA\\FONTS\\CONVFONT.SHP"); // Unknown
    ExploreImages(mainFont->data,mainFont->size);
    */
    
    
    /*
     TreArchive misc ;
     misc.InitFromFile("MISC.TRE");
     TreEntry* mainFont = misc.GetEntryByName("..\\..\\DATA\\FONTS\\DETLOPT.SHP"); // Details options
     ExploreImages(mainFont->data,mainFont->size);
    */
    
    /*
    TreArchive misc ;
    misc.InitFromFile("MISC.TRE");
    TreEntry* mainFont = misc.GetEntryByName("..\\..\\DATA\\FONTS\\FLITOPT.SHP"); // Control options
    ExploreImages(mainFont->data,mainFont->size);
    */
    
    /*
    TreArchive misc ;
    misc.InitFromFile("MISC.TRE");
    TreEntry* mainFont = misc.GetEntryByName("..\\..\\DATA\\FONTS\\FORMFONT.SHP"); // Font option
    ExploreImages(mainFont->data,mainFont->size);
    */
    
    /*
    TreArchive misc ;
    misc.InitFromFile("MISC.TRE");
    TreEntry* mainFont = misc.GetEntryByName("..\\..\\DATA\\FONTS\\GAMEOPT.SHP"); // Gameplay option
    ExploreImages(mainFont->data,mainFont->size);
    */
    
    /*
    TreArchive misc ;
    misc.InitFromFile("MISC.TRE");
    TreEntry* mainFont = misc.GetEntryByName("..\\..\\DATA\\FONTS\\GRAVFONT.SHP"); // Gameplay option
    ExploreImages(mainFont->data,mainFont->size);
    */
    
    /*
    TreArchive misc ;
    misc.InitFromFile("MISC.TRE");
    TreEntry* mainFont = misc.GetEntryByName("..\\..\\DATA\\FONTS\\MENBGRND.SHP"); // DogFight background
    ExploreImages(mainFont->data,mainFont->size);
    */
    
    /*
    TreArchive misc ;
    misc.InitFromFile("MISC.TRE");
    TreEntry* mainFont = misc.GetEntryByName("..\\..\\DATA\\FONTS\\MTYPEBUT.SHP"); // Dogfight/Search&Destroy ...WHY is is duplicated from MAINMENU.PAK??
    ExploreImages(mainFont->data,mainFont->size);
    */
    
    /*
    TreArchive misc ;
    misc.InitFromFile("MISC.TRE");
    TreEntry* mainFont = misc.GetEntryByName("..\\..\\DATA\\FONTS\\OVBKGRND.SHP"); // Object Viewer background ...WHY is is duplicated from OBJVIEW.PAK??
    ExploreImages(mainFont->data,mainFont->size);
    */
    
    /*
    TreArchive misc ;
    misc.InitFromFile("MISC.TRE");
    TreEntry* mainFont = misc.GetEntryByName("..\\..\\DATA\\FONTS\\RESTART.SHP"); // Restart menu
    ExploreImages(mainFont->data,mainFont->size);
    */
    
    /*
    TreArchive mis ;
    mis.InitFromFile("MISSIONS.TRE");
    TreEntry* misE = mis.GetEntryByName("..\\..\\DATA\\COCKPITS\\BETTY.PAK");    //
    ExploreImages(misE->data,misE->size);
    */
    
    /*
    TreArchive gf ;
    gf.InitFromFile("GAMEFLOW.TRE");
    TreEntry* mid1 = gf.GetEntryByName("..\\..\\DATA\\MIDGAMES\\MIDGAMES.PAK");
    ExploreImages(mid1->data,mid1->size);
    */
    
    /*
    TreArchive gf ;
    gf.InitFromFile("GAMEFLOW.TRE");
    TreEntry* mid1 = gf.GetEntryByName("..\\..\\DATA\\GAMEFLOW\\TM.SHP");  //Training mission builder dialog
    ExploreImages(mid1->data,mid1->size);
    */
    
    /*
    TreArchive gf ;
    gf.InitFromFile("GAMEFLOW.TRE");
    TreEntry* mid1 = gf.GetEntryByName("..\\..\\DATA\\GAMEFLOW\\MAINMENU.PAK");  //Main Menu buttons. No background :( !
    ExploreImages(mid1->data,mid1->size);
    */
    
    
    /*
    TreArchive gf ;
    gf.InitFromFile("GAMEFLOW.TRE");
    TreEntry* mid1 = gf.GetEntryByName("..\\..\\DATA\\GAMEFLOW\\CONVSHPS.PAK");  // ALL SETS AND CHARACTERS !!!!!
    ExploreImages(mid1->data,mid1->size);
    //Check palettes fro that too
    TreEntry* palettesEConv = gf.GetEntryByName("..\\..\\DATA\\GAMEFLOW\\CONVPALS.PAK");
    PakArchive palettesArchiveConv ;
    palettesArchiveConv.InitFromRAM("CONVPALS.PAK", palettesEConv->data, palettesEConv->size);
    palettesArchiveConv.List(stdout);
    */
    

    
    
    TreArchive gf ;
    gf.InitFromFile("GAMEFLOW.TRE");
    TreEntry* mid1 = gf.GetEntryByName("..\\..\\DATA\\GAMEFLOW\\OPTSHPS.PAK");  // A LLOOOOOOT OF GOOOD STUFFF !!! Background, bar animations, all airplanes
                                                                                // airplane preparation,
    ExploreImages(mid1->data,mid1->size,0);

    //Check palettes fro that too
    TreEntry* palettesE = gf.GetEntryByName("..\\..\\DATA\\GAMEFLOW\\OPTPALS.PAK");
    PakArchive palettesArchive ;
    palettesArchive.InitFromRAM("OPTPALS.PAK", palettesE->data, palettesE->size);
    palettesArchive.List(stdout);
    
    
    
    
    
    /*
    TreArchive misc ;
    misc.InitFromFile("MISC.TRE");
    TreEntry* mainFont = misc.GetEntryByName("..\\..\\DATA\\FONTS\\MAINOPT.SHP");
    ExploreImages(mainFont->data,mainFont->size);
     */
    
    /*
    TreArchive obj ;
    obj.InitFromFile("OBJECTS.TRE");
    TreEntry* objE = obj.GetEntryByName("..\\..\\DATA\\OBJECTS\\EJECT.PAK");   //Eject/Crash animation
    ExploreImages(objE->data,objE->size);
    */
}

int mainLibFreeSpace( int argc,char** argv){
    
    SetBase("/Users/fabiensanglard/SC/SC/");
    
    TestMouseCursor();
    
    return 0;

//    listTRE();
//    return 0;
    
//    ExploreRootIFFS();
//    return 0;
    
    /*
    TreArchive archiveSound ;
    archiveSound.InitFromFile("SOUND.TRE");
    archiveSound.List(stdout);
    
    
    TreArchive archive ;
    archive.InitFromFile("GAMEFLOW.TRE");
    archive.List(stdout);
    
    RSImage screen;
    screen.Create("Screen",320, 200);
    
    RLECodex codex;
    size_t byteRead;
    codex.ReadImage(archive.GetData()+5824512, &screen, &byteRead);
    
    renderer.Init(320, 200);
    
    renderer.ShowWindow();
    renderer.Pause();
    while(renderer.IsPaused()){
        renderer.DrawImage(&screen, 1);
        renderer.Swap();
    }
    */
    
    //Render palette
    /*
    renderer.Init(512, 512);
    renderer.SetClearColor(255,0,255);
    renderer.Clear();
    renderer.ShowPalette(renderer.GetDefaultPalette());
    */
    
    
    /*
    SetBase("/Users/fabiensanglard/Desktop/ARENA.PAK.CONTENT/");
    PakArchive archiveMauritan ;
    archiveMauritan.InitFromFile("FILE1.TXT");
    archiveMauritan.Decompress("/Users/fabiensanglard/Desktop/ARENA.PAK.CONTENT/MIP_MAX/", "MIP_MAX");
    
    PakArchive f ;
    f.InitFromFile("FILE2.TXT");
    f.Decompress("/Users/fabiensanglard/Desktop/ARENA.PAK.CONTENT/MIP_MED/", "MIP_MED");
    
    PakArchive g ;
    g.InitFromFile("FILE3.TXT");
    g.Decompress("/Users/fabiensanglard/Desktop/ARENA.PAK.CONTENT/MIP_MIN/", "MIP_MIN");
    */
    
    /*
    PakArchive archiveMauritan ;
    archiveMauritan.InitFromFile("ARENA.PAK");
    archiveMauritan.Decompress("/Users/fabiensanglard/Desktop/", "TXT");
    */
    
    
    /*
    testShowAllTexturesPAK();
    return 0;
    */
    
    //WIP
    /*
    renderer.Init(640, 400);
    TreArchive tre;
    tre.InitFromFile("GAMEFLOW.TRE");
    
    TreEntry* pakToExplore = tre.GetEntryByName("..\\..\\DATA\\MIDGAMES\\MID1.PAK");
    
    PakArchive arch;
    arch.InitFromRAM("MID1.PAK",pakToExplore->data,pakToExplore->size);
    
    printf("MID1.PAK" " contains %lu entries\n.",arch.GetNumEntries());
    
    for(size_t i =0 ;i < arch.GetNumEntries() ; i++){
        
        PakEntry* entry = arch.GetEntry(i);
        PakArchive a;
        a.InitFromRAM("", entry->data, entry->size);
        showAllImageInArchive(&a);
    }
    return 0;
    */
    
    
    /*
    SCMainMenu mainMenu;
    mainMenu.Init();
    mainMenu.Run();
    return 0;
    */

    /* 
    SCDogFightMenu dogFightMenu;
    dogFightMenu.Init();
    dogFightMenu.Run();
    return 0;
    */
    
    
    SCObjectViewer viewer;
    viewer.Init();
    viewer.Run();
    return 0;
    
    
    /*
    PakArchive archiveCanyon ;
    archiveCanyon.InitFromFile("CANYON.PAK");
    archiveCanyon.Decompress("/Users/fabiensanglard/Desktop/", "TXT");

    PakArchive archiveMauritan ;
    archiveMauritan.InitFromFile("MAURITAN.PAK");
    archiveMauritan.Decompress("/Users/fabiensanglard/Desktop/", "TXT");

    return 0;
    */
    
    
    
    
    //testShowAllTexturesPAK();
    
    
    RSArea* area = new RSArea();

    area->InitFromPAKFileName("ARENA.PAK");
    area->InitFromPAKFileName("ALASKA.PAK");
    area->InitFromPAKFileName("EUROPE.PAK");
    // // NOT A MAP !area.InitFromPAKFileName("MSFILES.PAK");
    area->InitFromPAKFileName("SANFRAN.PAK");
    area->InitFromPAKFileName("ANDMAL1.PAK");
    area->InitFromPAKFileName("CANYON.PAK");
    // // NOT A MAP !area.InitFromPAKFileName("MAPDATA.PAK");
    area->InitFromPAKFileName("QUEBEC.PAK");
    area->InitFromPAKFileName("TURKEY.PAK");
    area->InitFromPAKFileName("ANDMAL2.PAK");
    area->InitFromPAKFileName("EGYPT.PAK");
    area->InitFromPAKFileName("MAURITAN.PAK");
    area->InitFromPAKFileName("RHODEI.PAK");
    
}