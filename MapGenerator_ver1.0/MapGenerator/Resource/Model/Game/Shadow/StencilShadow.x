xof 0302txt 0064
template Header {
 <3D82AB43-62DA-11cf-AB39-0020AF71E433>
 WORD major;
 WORD minor;
 DWORD flags;
}

template Vector {
 <3D82AB5E-62DA-11cf-AB39-0020AF71E433>
 FLOAT x;
 FLOAT y;
 FLOAT z;
}

template Coords2d {
 <F6F23F44-7686-11cf-8F52-0040333594A3>
 FLOAT u;
 FLOAT v;
}

template Matrix4x4 {
 <F6F23F45-7686-11cf-8F52-0040333594A3>
 array FLOAT matrix[16];
}

template ColorRGBA {
 <35FF44E0-6C7C-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
 FLOAT alpha;
}

template ColorRGB {
 <D3E16E81-7835-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
}

template IndexedColor {
 <1630B820-7842-11cf-8F52-0040333594A3>
 DWORD index;
 ColorRGBA indexColor;
}

template Boolean {
 <4885AE61-78E8-11cf-8F52-0040333594A3>
 WORD truefalse;
}

template Boolean2d {
 <4885AE63-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template MaterialWrap {
 <4885AE60-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template TextureFilename {
 <A42790E1-7810-11cf-8F52-0040333594A3>
 STRING filename;
}

template Material {
 <3D82AB4D-62DA-11cf-AB39-0020AF71E433>
 ColorRGBA faceColor;
 FLOAT power;
 ColorRGB specularColor;
 ColorRGB emissiveColor;
 [...]
}

template MeshFace {
 <3D82AB5F-62DA-11cf-AB39-0020AF71E433>
 DWORD nFaceVertexIndices;
 array DWORD faceVertexIndices[nFaceVertexIndices];
}

template MeshFaceWraps {
 <4885AE62-78E8-11cf-8F52-0040333594A3>
 DWORD nFaceWrapValues;
 Boolean2d faceWrapValues;
}

template MeshTextureCoords {
 <F6F23F40-7686-11cf-8F52-0040333594A3>
 DWORD nTextureCoords;
 array Coords2d textureCoords[nTextureCoords];
}

template MeshMaterialList {
 <F6F23F42-7686-11cf-8F52-0040333594A3>
 DWORD nMaterials;
 DWORD nFaceIndexes;
 array DWORD faceIndexes[nFaceIndexes];
 [Material]
}

template MeshNormals {
 <F6F23F43-7686-11cf-8F52-0040333594A3>
 DWORD nNormals;
 array Vector normals[nNormals];
 DWORD nFaceNormals;
 array MeshFace faceNormals[nFaceNormals];
}

template MeshVertexColors {
 <1630B821-7842-11cf-8F52-0040333594A3>
 DWORD nVertexColors;
 array IndexedColor vertexColors[nVertexColors];
}

template Mesh {
 <3D82AB44-62DA-11cf-AB39-0020AF71E433>
 DWORD nVertices;
 array Vector vertices[nVertices];
 DWORD nFaces;
 array MeshFace faces[nFaces];
 [...]
}

Header{
1;
0;
1;
}

Mesh {
 62;
 0.00000;1.50000;-0.50000;,
 0.20337;1.50000;-0.45677;,
 0.20337;-1.50000;-0.45677;,
 0.00000;-1.50000;-0.50000;,
 0.37157;1.50000;-0.33457;,
 0.37157;-1.50000;-0.33457;,
 0.47553;1.50000;-0.15451;,
 0.47553;-1.50000;-0.15451;,
 0.49726;1.50000;0.05226;,
 0.49726;-1.50000;0.05226;,
 0.43301;1.50000;0.25000;,
 0.43301;-1.50000;0.25000;,
 0.29389;1.50000;0.40451;,
 0.29389;-1.50000;0.40451;,
 0.10396;1.50000;0.48907;,
 0.10396;-1.50000;0.48907;,
 -0.10396;1.50000;0.48907;,
 -0.10396;-1.50000;0.48907;,
 -0.29389;1.50000;0.40451;,
 -0.29389;-1.50000;0.40451;,
 -0.43301;1.50000;0.25000;,
 -0.43301;-1.50000;0.25000;,
 -0.49726;1.50000;0.05226;,
 -0.49726;-1.50000;0.05226;,
 -0.47553;1.50000;-0.15451;,
 -0.47553;-1.50000;-0.15451;,
 -0.37157;1.50000;-0.33457;,
 -0.37157;-1.50000;-0.33457;,
 -0.20337;1.50000;-0.45677;,
 -0.20337;-1.50000;-0.45677;,
 0.00000;1.50000;-0.50000;,
 0.00000;-1.50000;-0.50000;,
 0.00000;1.50000;0.00000;,
 0.00000;1.50000;0.00000;,
 0.00000;1.50000;0.00000;,
 0.00000;1.50000;0.00000;,
 0.00000;1.50000;0.00000;,
 0.00000;1.50000;0.00000;,
 0.00000;1.50000;0.00000;,
 0.00000;1.50000;0.00000;,
 0.00000;1.50000;0.00000;,
 0.00000;1.50000;0.00000;,
 0.00000;1.50000;0.00000;,
 0.00000;1.50000;0.00000;,
 0.00000;1.50000;0.00000;,
 0.00000;1.50000;0.00000;,
 0.00000;1.50000;0.00000;,
 0.00000;-1.50000;-0.00000;,
 0.00000;-1.50000;-0.00000;,
 0.00000;-1.50000;-0.00000;,
 0.00000;-1.50000;-0.00000;,
 0.00000;-1.50000;-0.00000;,
 0.00000;-1.50000;-0.00000;,
 0.00000;-1.50000;-0.00000;,
 0.00000;-1.50000;-0.00000;,
 0.00000;-1.50000;-0.00000;,
 0.00000;-1.50000;-0.00000;,
 0.00000;-1.50000;-0.00000;,
 0.00000;-1.50000;-0.00000;,
 0.00000;-1.50000;-0.00000;,
 0.00000;-1.50000;-0.00000;,
 0.00000;-1.50000;-0.00000;;
 
 45;
 4;0,1,2,3;,
 4;1,4,5,2;,
 4;4,6,7,5;,
 4;6,8,9,7;,
 4;8,10,11,9;,
 4;10,12,13,11;,
 4;12,14,15,13;,
 4;14,16,17,15;,
 4;16,18,19,17;,
 4;18,20,21,19;,
 4;20,22,23,21;,
 4;22,24,25,23;,
 4;24,26,27,25;,
 4;26,28,29,27;,
 4;28,30,31,29;,
 3;32,1,0;,
 3;33,4,1;,
 3;34,6,4;,
 3;35,8,6;,
 3;36,10,8;,
 3;37,12,10;,
 3;38,14,12;,
 3;39,16,14;,
 3;40,18,16;,
 3;41,20,18;,
 3;42,22,20;,
 3;43,24,22;,
 3;44,26,24;,
 3;45,28,26;,
 3;46,30,28;,
 3;47,3,2;,
 3;48,2,5;,
 3;49,5,7;,
 3;50,7,9;,
 3;51,9,11;,
 3;52,11,13;,
 3;53,13,15;,
 3;54,15,17;,
 3;55,17,19;,
 3;56,19,21;,
 3;57,21,23;,
 3;58,23,25;,
 3;59,25,27;,
 3;60,27,29;,
 3;61,29,31;;
 
 MeshMaterialList {
  1;
  45;
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0;;
  Material {
   1.000000;1.000000;1.000000;1.000000;;
   0.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  17;
  0.000000;1.000000;0.000000;,
  0.000000;0.000000;-1.000000;,
  0.406737;0.000000;-0.913545;,
  0.743145;0.000000;-0.669131;,
  0.951057;0.000000;-0.309017;,
  0.994522;0.000000;0.104528;,
  0.866025;0.000000;0.500000;,
  0.587785;0.000000;0.809017;,
  0.207912;0.000000;0.978148;,
  -0.207912;0.000000;0.978148;,
  -0.587785;0.000000;0.809017;,
  -0.866025;0.000000;0.500000;,
  -0.994522;0.000000;0.104528;,
  -0.951056;0.000000;-0.309017;,
  -0.743145;0.000000;-0.669131;,
  -0.406737;0.000000;-0.913545;,
  0.000000;-1.000000;-0.000000;;
  45;
  4;1,2,2,1;,
  4;2,3,3,2;,
  4;3,4,4,3;,
  4;4,5,5,4;,
  4;5,6,6,5;,
  4;6,7,7,6;,
  4;7,8,8,7;,
  4;8,9,9,8;,
  4;9,10,10,9;,
  4;10,11,11,10;,
  4;11,12,12,11;,
  4;12,13,13,12;,
  4;13,14,14,13;,
  4;14,15,15,14;,
  4;15,1,1,15;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;16,16,16;,
  3;16,16,16;,
  3;16,16,16;,
  3;16,16,16;,
  3;16,16,16;,
  3;16,16,16;,
  3;16,16,16;,
  3;16,16,16;,
  3;16,16,16;,
  3;16,16,16;,
  3;16,16,16;,
  3;16,16,16;,
  3;16,16,16;,
  3;16,16,16;,
  3;16,16,16;;
 }
 MeshTextureCoords {
  62;
  0.000000;0.000000;,
  0.066667;0.000000;,
  0.066667;1.000000;,
  0.000000;1.000000;,
  0.133333;0.000000;,
  0.133333;1.000000;,
  0.200000;0.000000;,
  0.200000;1.000000;,
  0.266667;0.000000;,
  0.266667;1.000000;,
  0.333333;0.000000;,
  0.333333;1.000000;,
  0.400000;0.000000;,
  0.400000;1.000000;,
  0.466667;0.000000;,
  0.466667;1.000000;,
  0.533333;0.000000;,
  0.533333;1.000000;,
  0.600000;0.000000;,
  0.600000;1.000000;,
  0.666667;0.000000;,
  0.666667;1.000000;,
  0.733333;0.000000;,
  0.733333;1.000000;,
  0.800000;0.000000;,
  0.800000;1.000000;,
  0.866667;0.000000;,
  0.866667;1.000000;,
  0.933333;0.000000;,
  0.933333;1.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.033333;0.000000;,
  0.100000;0.000000;,
  0.166667;0.000000;,
  0.233333;0.000000;,
  0.300000;0.000000;,
  0.366667;0.000000;,
  0.433333;0.000000;,
  0.500000;0.000000;,
  0.566667;0.000000;,
  0.633333;0.000000;,
  0.700000;0.000000;,
  0.766667;0.000000;,
  0.833333;0.000000;,
  0.900000;0.000000;,
  0.966667;0.000000;,
  0.033333;1.000000;,
  0.100000;1.000000;,
  0.166667;1.000000;,
  0.233333;1.000000;,
  0.300000;1.000000;,
  0.366667;1.000000;,
  0.433333;1.000000;,
  0.500000;1.000000;,
  0.566667;1.000000;,
  0.633333;1.000000;,
  0.700000;1.000000;,
  0.766667;1.000000;,
  0.833333;1.000000;,
  0.900000;1.000000;,
  0.966667;1.000000;;
 }
}