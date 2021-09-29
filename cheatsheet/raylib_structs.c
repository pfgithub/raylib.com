
    void DrawTextRecEx(Font font, const char *text, Rectangle rec, float fontSize, float spacing, bool wordWrap, Color tint,
    struct Vector2 {float x; float y;}; // Vector2, 2 components
    struct Vector3 {float x; float y; float z;}; // Vector3, 3 components
    struct Vector4 {float x; float y; float z; float w;}; // Vector4, 4 components
    typedef Vector4 Quaternion; // Quaternion, 4 components (Vector4 alias)
    struct Matrix {float m0, m4, m8, m12;  float m1, m5, m9, m13;  float m2, m6, m10, m14; float m3, m7, m11, m15;}; // Matrix, 4x4 components, column major, OpenGL style, right handed
    struct Color {unsigned char r; unsigned char g; unsigned char b; unsigned char a;}; // Color, 4 components, R8G8B8A8 (32bit)
    struct Rectangle {float x; float y; float width; float height;}; // Rectangle, 4 components

    struct Image {void *data; int width; int height; int mipmaps; int format;}; // Image, pixel data stored in CPU memory (RAM)
    struct Texture {unsigned int id; int width; int height; int mipmaps; int format;}; // Texture, tex data stored in GPU memory (VRAM)
    typedef Texture Texture2D; // Texture2D, same as Texture
    typedef Texture TextureCubemap; // TextureCubemap, same as Texture

    struct RenderTexture {unsigned int id; Texture texture; Texture depth;}; // RenderTexture, fbo for texture rendering
    typedef RenderTexture RenderTexture2D; // RenderTexture2D, same as RenderTexture

    struct NPatchInfo {Rectangle source; int left; int top; int right; int bottom; int layout;}; // NPatchInfo, n-patch layout info

    // GlyphInfo, font characters glyphs info
    typedef struct GlyphInfo {
        int value;              // Character value (Unicode)
        int offsetX;            // Character offset X when drawing
        int offsetY;            // Character offset Y when drawing
        int advanceX;           // Character advance position X
        Image image;            // Character image data
    } GlyphInfo;

    // Font, font texture and GlyphInfo array data
    typedef struct Font {
        int baseSize;           // Base size (default chars height)
        int glyphCount;         // Number of glyph characters
        int glyphPadding;       // Padding around the glyph characters
        Texture2D texture;      // Texture atlas containing the glyphs
        Rectangle *recs;        // Rectangles in texture for the glyphs
        GlyphInfo *glyphs;      // Glyphs info data
    } Font;

    // Camera, defines position/orientation in 3d space
    typedef struct Camera3D {
        Vector3 position;       // Camera position
        Vector3 target;         // Camera target it looks-at
        Vector3 up;             // Camera up vector (rotation over its axis)
        float fovy;             // Camera field-of-view apperture in Y (degrees) in perspective, used as near plane width in orthographic
        int projection;         // Camera projection: CAMERA_PERSPECTIVE or CAMERA_ORTHOGRAPHIC
    } Camera3D;

    typedef Camera3D Camera;    // Camera type fallback, defaults to Camera3D

    // Camera2D, defines position/orientation in 2d space
    typedef struct Camera2D {
        Vector2 offset;         // Camera offset (displacement from target)
        Vector2 target;         // Camera target (rotation and zoom origin)
        float rotation;         // Camera rotation in degrees
        float zoom;             // Camera zoom (scaling), should be 1.0f by default
    } Camera2D;

    // Mesh, vertex data and vao/vbo
    typedef struct Mesh {
        int vertexCount;        // Number of vertices stored in arrays
        int triangleCount;      // Number of triangles stored (indexed or not)

        // Vertex attributes data
        float *vertices;        // Vertex position (XYZ - 3 components per vertex) (shader-location = 0)
        float *texcoords;       // Vertex texture coordinates (UV - 2 components per vertex) (shader-location = 1)
        float *texcoords2;      // Vertex second texture coordinates (useful for lightmaps) (shader-location = 5)
        float *normals;         // Vertex normals (XYZ - 3 components per vertex) (shader-location = 2)
        float *tangents;        // Vertex tangents (XYZW - 4 components per vertex) (shader-location = 4)
        unsigned char *colors;      // Vertex colors (RGBA - 4 components per vertex) (shader-location = 3)
        unsigned short *indices;    // Vertex indices (in case vertex data comes indexed)

        // Animation vertex data
        float *animVertices;    // Animated vertex positions (after bones transformations)
        float *animNormals;     // Animated normals (after bones transformations)
        int *boneIds;           // Vertex bone ids, up to 4 bones influence by vertex (skinning)
        float *boneWeights;     // Vertex bone weight, up to 4 bones influence by vertex (skinning)

        // OpenGL identifiers
        unsigned int vaoId;     // OpenGL Vertex Array Object id
        unsigned int *vboId;    // OpenGL Vertex Buffer Objects id (default vertex data)
    } Mesh;

    // Shader
    typedef struct Shader {
        unsigned int id;        // Shader program id
        int *locs;              // Shader locations array (RL_MAX_SHADER_LOCATIONS)
    } Shader;

    // MaterialMap
    typedef struct MaterialMap {
        Texture2D texture;      // Material map texture
        Color color;            // Material map color
        float value;            // Material map value
    } MaterialMap;

    // Material, includes shader and maps
    typedef struct Material {
        Shader shader;          // Material shader
        MaterialMap *maps;      // Material maps array (MAX_MATERIAL_MAPS)
        float params[4];        // Material generic parameters (if required)
    } Material;

    // Transform, vectex transformation data
    typedef struct Transform {
        Vector3 translation;    // Translation
        Quaternion rotation;    // Rotation
        Vector3 scale;          // Scale
    } Transform;

    // Bone, skeletal animation bone
    typedef struct BoneInfo {
        char name[32];          // Bone name
        int parent;             // Bone parent
    } BoneInfo;

    // Model, meshes, materials and animation data
    typedef struct Model {
        Matrix transform;       // Local transform matrix

        int meshCount;          // Number of meshes
        int materialCount;      // Number of materials
        Mesh *meshes;           // Meshes array
        Material *materials;    // Materials array
        int *meshMaterial;      // Mesh material number

        // Animation data
        int boneCount;          // Number of bones
        BoneInfo *bones;        // Bones information (skeleton)
        Transform *bindPose;    // Bones base transformation (pose)
    } Model;

    // ModelAnimation
    typedef struct ModelAnimation {
        int boneCount;          // Number of bones
        int frameCount;         // Number of animation frames
        BoneInfo *bones;        // Bones information (skeleton)
        Transform **framePoses; // Poses array by frame
    } ModelAnimation;

    // Ray, ray for raycasting
    typedef struct Ray {
        Vector3 position;       // Ray position (origin)
        Vector3 direction;      // Ray direction
    } Ray;

    // RayCollision, ray hit information
    typedef struct RayCollision {
        bool hit;               // Did the ray hit something?
        float distance;         // Distance to nearest hit
        Vector3 point;          // Point of nearest hit
        Vector3 normal;         // Surface normal of hit
    } RayCollision;

    // BoundingBox
    typedef struct BoundingBox {
        Vector3 min;            // Minimum vertex box-corner
        Vector3 max;            // Maximum vertex box-corner
    } BoundingBox;

    // Wave, audio wave data
    typedef struct Wave {
        unsigned int frameCount;    // Total number of frames (considering channels)
        unsigned int sampleRate;    // Frequency (samples per second)
        unsigned int sampleSize;    // Bit depth (bits per sample): 8, 16, 32 (24 not supported)
        unsigned int channels;      // Number of channels (1-mono, 2-stereo, ...)
        void *data;                 // Buffer data pointer
    } Wave;

    typedef struct rAudioBuffer rAudioBuffer;

    // AudioStream, custom audio stream
    typedef struct AudioStream {
        rAudioBuffer *buffer;       // Pointer to internal data used by the audio system

        unsigned int sampleRate;    // Frequency (samples per second)
        unsigned int sampleSize;    // Bit depth (bits per sample): 8, 16, 32 (24 not supported)
        unsigned int channels;      // Number of channels (1-mono, 2-stereo, ...)
    } AudioStream;

    // Sound
    typedef struct Sound {
        AudioStream stream;         // Audio stream
        unsigned int frameCount;    // Total number of frames (considering channels)
    } Sound;

    // Music, audio stream, anything longer than ~10 seconds should be streamed
    typedef struct Music {
        AudioStream stream;         // Audio stream
        unsigned int frameCount;    // Total number of frames (considering channels)
        bool looping;               // Music looping enable

        int ctxType;                // Type of music context (audio filetype)
        void *ctxData;              // Audio context data, depends on type
    } Music;

    // VrDeviceInfo, Head-Mounted-Display device parameters
    typedef struct VrDeviceInfo {
        int hResolution;                // Horizontal resolution in pixels
        int vResolution;                // Vertical resolution in pixels
        float hScreenSize;              // Horizontal size in meters
        float vScreenSize;              // Vertical size in meters
        float vScreenCenter;            // Screen center in meters
        float eyeToScreenDistance;      // Distance between eye and display in meters
        float lensSeparationDistance;   // Lens separation distance in meters
        float interpupillaryDistance;   // IPD (distance between pupils) in meters
        float lensDistortionValues[4];  // Lens distortion constant parameters
        float chromaAbCorrection[4];    // Chromatic aberration correction parameters
    } VrDeviceInfo;

    // VrStereoConfig, VR stereo rendering configuration for simulator
    typedef struct VrStereoConfig {
        Matrix projection[2];           // VR projection matrices (per eye)
        Matrix viewOffset[2];           // VR view offset matrices (per eye)
        float leftLensCenter[2];        // VR left lens center
        float rightLensCenter[2];       // VR right lens center
        float leftScreenCenter[2];      // VR left screen center
        float rightScreenCenter[2];     // VR right screen center
        float scale[2];                 // VR distortion scale
        float scaleIn[2];               // VR distortion scale in
    } VrStereoConfig;
