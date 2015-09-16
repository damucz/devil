#include <IwGx.h>
#include <s3eKeyboard.h>
#include <s3ePointer.h>
#include <IL/il.h>

CIwTexture* tex = NULL;
ILuint imgId = -1;
float x = 50.0f;
float y = 50.0f;
float w = 200.0f;
float h = 200.0f;
float framerate = 60.0f;
int frame = 1;
uint32 time = 0;

void Update(uint32 dt)          // dt is in ms
{
    time += dt;
    int duration = ilGetInteger(IL_IMAGE_DURATION);
    //IwTrace(ILTEST, ("dur=%d time=%d dt=%d", duration, time, dt));
    if (duration > 0 && time > duration)
    {
        time -= duration;
        if (ilGetInteger(IL_NUM_IMAGES) == 0)           // no frame in queue, loop
            frame = 1;
        else
            ++frame;

        ilBindImage(imgId);
        ILboolean x = ilActiveImage(frame);

        ilConvertImage(IL_BGRA, IL_UNSIGNED_BYTE);
        int type = ilGetInteger(IL_IMAGE_FORMAT);
        int width = ilGetInteger(IL_IMAGE_WIDTH);
        int height = ilGetInteger(IL_IMAGE_HEIGHT);
        int bpp = ilGetInteger(IL_IMAGE_BYTES_PER_PIXEL);

        CIwImage::Format format;
        switch (type)
        {
        case IL_RGBA: format = CIwImage::ABGR_8888; break;
        case IL_BGRA: format = CIwImage::ARGB_8888; break;
        case IL_BGR: format = CIwImage::RGB_888; break;
        default:
            IwAssert(ILTEST, false);
        }

        tex->CopyFromBuffer(width, height, format, width*bpp, ilGetData(), NULL);
        tex->ChangeTexels(tex->GetTexels(), format);
#if 0
        delete tex;
        tex = new CIwTexture();
        tex->SetModifiable(true);
        tex->SetMipMapping(false);
        tex->CopyFromBuffer(width, height, format, width*bpp, ilGetData(), /*(uint16*)ilGetPalette()*/ NULL);
        tex->Upload();
#endif
        //ILenum e = ilGetError();

        //IwTrace(ILTEST, ("w=%d h=%d bpp=%d", width, height, bpp));
        //IwTrace(ILTEST, ("frame=%d numimages=%d imageduration=%d", frame, ilGetInteger(IL_NUM_IMAGES), ilGetInteger(IL_IMAGE_DURATION)));
    }
}

void Render()
{
    CIwColour usedColor;
    usedColor.Set(255, 255, 255, 255);
    CIwColour *colors = IW_GX_ALLOC(CIwColour, 4);
    colors[0] = usedColor;
    colors[1] = usedColor;
    colors[2] = usedColor;
    colors[3] = usedColor;

    CIwFVec2 *verts2 = IW_GX_ALLOC(CIwFVec2, 4);
    verts2[0].x = x;
    verts2[0].y = y;
    verts2[1].x = verts2[0].x;
    verts2[1].y = y + h;
    verts2[2].x = x + w;
    verts2[2].y = verts2[1].y;
    verts2[3].x = verts2[2].x;
    verts2[3].y = verts2[0].y;

    CIwFVec2 *uvs = IW_GX_ALLOC(CIwFVec2, 4);
    uvs[0].x = 0.0f;
    uvs[0].y = 0.0f;
    uvs[1].x = uvs[0].x;
    uvs[1].y = 1.0f;
    uvs[2].x = 1.0f;
    uvs[2].y = uvs[1].y;
    uvs[3].x = uvs[2].x;
    uvs[3].y = uvs[0].y;

    IwGxSetUVStream(uvs);
    IwGxSetVertStreamScreenSpace(verts2, 4);
    IwGxSetColStream(colors, 4);
    IwGxSetNormStream(NULL);

    CIwMaterial* mat = IW_GX_ALLOC_MATERIAL();
    mat->SetCullMode(CIwMaterial::CULL_NONE);
    mat->SetTexture(tex);
    mat->SetDepthWriteMode(CIwMaterial::DEPTH_WRITE_DISABLED);
    mat->SetAlphaMode(CIwMaterial::ALPHA_BLEND);
    IwGxSetMaterial(mat);

    IwGxDrawPrims(IW_GX_QUAD_LIST, NULL, 4);

    IwGxPrintFrameRate(10, 10);
}

void HandleDevILErrors()
{
    ILenum error = ilGetError();

    if (error != IL_NO_ERROR) {
        do {
            printf("\n\n%d\n", error);
        } while ((error = ilGetError()));

        exit(1);
    }
}

void LoadTexture()
{
    //const char* FileName = "gradient.png";
    const char* FileName = "bart.gif";
    //const char* FileName = "pika.gif";
    //const char* FileName = "alphatest.png";

    // Needed to initialize DevIL.
    ilInit();

    // GL cannot use palettes anyway, so convert early.
    //ilEnable(IL_CONV_PAL);

    // Generate the main image name to use.
    ilGenImages(1, &imgId);

    // Bind this image name.
    ilBindImage(imgId);

    // Loads the image specified by File into the ImgId image.
    if (!ilLoadImage(FileName)) {
        HandleDevILErrors();
    }

    // Make sure the window is in the same proportions as the image.
    //  Generate the appropriate width x height less than or equal to MAX_X x MAX_Y.
    //	Instead of just clipping Width x Height to MAX_X x MAX_Y, we scale to
    //	an appropriate size, so the image isn't stretched/squished.
    int width = ilGetInteger(IL_IMAGE_WIDTH);
    int height = ilGetInteger(IL_IMAGE_HEIGHT);

    IwTrace(ILTEST, ("%s: %d x %d (%d images)", FileName, width, height, ilGetInteger(IL_NUM_IMAGES)));

    //ilLoadL(IL_TGA, Lump, Size);
    //free(Lump);
}

void ReleaseTexture()
{
    // We're done with our image, so we go ahead and delete it.
    ilDeleteImages(1, &imgId);

    ilShutDown();
}

int main()
{
    IwGxInit();
    IwGxSetOrtho(0, IwGxGetDisplayWidth(), 0, IwGxGetDisplayHeight(), 1.0f, 10.0f);

    LoadTexture();
    tex = new CIwTexture();
    tex->SetModifiable(true);
    tex->SetMipMapping(false);
    //tex->LoadFromFile("gradient.png");
    int ttype = ilGetInteger(IL_IMAGE_FORMAT);
    ilConvertImage(IL_BGRA, IL_UNSIGNED_BYTE);
    int width = ilGetInteger(IL_IMAGE_WIDTH);
    int height = ilGetInteger(IL_IMAGE_HEIGHT);
    int bpp = ilGetInteger(IL_IMAGE_BYTES_PER_PIXEL);
    int type = ilGetInteger(IL_IMAGE_FORMAT);
    CIwImage::Format format;
    switch (type)
    {
    case IL_RGBA: format = CIwImage::ABGR_8888; break;
    case IL_BGRA: format = CIwImage::ARGB_8888; break;
    case IL_BGR: format = CIwImage::RGB_888; break;
    default:
        IwAssert(ILTEST, false);
    }
/*
#define IL_COLOUR_INDEX     0x1900
#define IL_COLOR_INDEX      0x1900
#define IL_ALPHA			0x1906
#define IL_RGB              0x1907
#define IL_RGBA             0x1908
#define IL_BGR              0x80E0
#define IL_BGRA             0x80E1
#define IL_LUMINANCE        0x1909
#define IL_LUMINANCE_ALPHA  0x190A
*/
    tex->CopyFromBuffer(width, height, format, width*bpp, ilGetData(), /*(uint16*)ilGetPalette()*/ NULL);
    tex->Upload();

    IwGxSetColClear(0, 0, 0, 255);

    uint64 currentTime = s3eTimerGetMs();

    while (!s3eDeviceCheckQuitRequest())
    {
        uint64 newTime = s3eTimerGetMs();
        int32 timePassed = (int32)(newTime - currentTime);

        int32 oneFrameTime = 1000 / framerate;
        if (timePassed >= oneFrameTime)
            s3eDeviceYield(0);
        else
            while (timePassed < oneFrameTime)
            {
                s3eDeviceYield((int32)(oneFrameTime - timePassed));

                newTime = s3eTimerGetMs();
                timePassed = (int32)(newTime - currentTime);
            }

        //IwTrace(Jerky, ("passed ms %ld", timePassed));

        currentTime = newTime;

        // Prevent back-light to off state
        s3eDeviceBacklightOn();

        s3ePointerUpdate();
        s3eKeyboardUpdate();

        Update(timePassed);

        IwGxClear(IW_GX_COLOUR_BUFFER_F | IW_GX_DEPTH_BUFFER_F);

        Render();

        IwGxFlush();
        IwGxSwapBuffers();
    }

    delete tex;

    ReleaseTexture();

    IwGxTerminate();
    return 0;
}
