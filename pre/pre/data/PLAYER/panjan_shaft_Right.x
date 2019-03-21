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
 120;
 15.23055;-0.00042;-6.53042;,
 15.23055;0.85198;-6.47454;,
 15.23055;-0.85281;-6.47454;,
 15.23055;1.68978;-6.30789;,
 15.23055;-1.69062;-6.30789;,
 15.23055;2.49867;-6.03331;,
 15.23055;-2.49950;-6.03331;,
 15.23055;3.26480;-5.65550;,
 15.23055;-3.26563;-5.65550;,
 15.23055;3.97506;-5.18092;,
 15.23055;-3.97589;-5.18093;,
 15.23055;-4.61813;-4.61770;,
 15.23055;4.61729;-4.61770;,
 15.23055;5.18052;-3.97545;,
 15.23055;-5.18135;-3.97546;,
 15.23055;-5.65593;-3.26520;,
 15.23055;5.65510;-3.26519;,
 15.23055;-6.03374;-2.49908;,
 15.23055;6.03291;-2.49906;,
 15.23055;-6.30832;-1.69018;,
 15.23055;6.30749;-1.69017;,
 15.23055;-6.47497;-0.85238;,
 15.23055;6.47413;-0.85236;,
 15.23055;-6.53084;0.00001;,
 15.23055;6.53000;0.00001;,
 15.23055;6.47413;0.85240;,
 15.23055;-6.47497;0.85240;,
 15.23055;6.30748;1.69020;,
 15.23055;-6.30832;1.69020;,
 15.23055;6.03290;2.49909;,
 15.23055;-6.03374;2.49910;,
 15.23055;5.65509;3.26522;,
 15.23055;-5.65593;3.26522;,
 15.23055;5.18051;3.97548;,
 15.23055;-5.18135;3.97548;,
 15.23054;4.61729;4.61771;,
 15.23055;-4.61812;4.61771;,
 15.23055;3.97505;5.18094;,
 15.23055;-3.97589;5.18094;,
 15.23055;3.26479;5.65551;,
 15.23055;-3.26563;5.65551;,
 15.23055;2.49866;6.03333;,
 15.23055;-2.49950;6.03333;,
 15.23055;1.68978;6.30790;,
 15.23055;-1.69062;6.30790;,
 15.23055;0.85197;6.47455;,
 15.23055;-0.85281;6.47455;,
 15.23055;-0.00042;6.53043;,
 12.47629;6.47413;-0.85237;,
 0.00000;6.47413;-0.85237;,
 0.00000;6.53000;-0.00000;,
 12.47629;6.53000;0.00001;,
 0.00000;6.30749;-1.69018;,
 0.00000;6.03291;-2.49907;,
 0.00000;5.65510;-3.26520;,
 0.00000;5.18052;-3.97546;,
 12.47629;5.18052;-3.97545;,
 12.47629;4.61729;-4.61769;,
 0.00000;4.61729;-4.61770;,
 12.47630;3.97506;-5.18092;,
 0.00001;3.97506;-5.18091;,
 0.00000;3.26480;-5.65551;,
 0.00000;2.49867;-6.03332;,
 0.00000;1.68978;-6.30790;,
 0.00001;0.85198;-6.47455;,
 12.47629;0.85198;-6.47454;,
 12.47629;-0.00042;-6.53042;,
 0.00001;-0.00042;-6.53042;,
 12.47629;-0.85281;-6.47454;,
 0.00001;-0.85281;-6.47455;,
 0.00000;-1.69062;-6.30790;,
 0.00000;-2.49950;-6.03332;,
 0.00000;-3.26563;-5.65551;,
 0.00001;-3.97589;-5.18093;,
 12.47630;-3.97589;-5.18093;,
 12.47629;-4.61813;-4.61769;,
 0.00000;-4.61813;-4.61770;,
 12.47629;-5.18135;-3.97546;,
 0.00000;-5.18135;-3.97547;,
 0.00000;-5.65593;-3.26521;,
 0.00000;-6.03374;-2.49908;,
 0.00000;-6.30832;-1.69019;,
 0.00000;-6.47497;-0.85239;,
 12.47629;-6.47497;-0.85238;,
 12.47629;-6.53084;0.00001;,
 0.00000;-6.53084;-0.00000;,
 12.47629;-6.47497;0.85239;,
 0.00000;-6.47497;0.85239;,
 0.00000;-6.30832;1.69020;,
 0.00000;-6.03374;2.49909;,
 0.00000;-5.65593;3.26521;,
 12.47629;-5.18135;3.97547;,
 0.00000;-5.18135;3.97547;,
 12.47629;-4.61812;4.61771;,
 -0.00000;-4.61812;4.61771;,
 12.47629;-3.97589;5.18094;,
 -0.00000;-3.97589;5.18093;,
 0.00000;-3.26563;5.65551;,
 -0.00000;-2.49950;6.03332;,
 -0.00000;-1.69062;6.30790;,
 12.47628;-0.85281;6.47455;,
 -0.00000;-0.85281;6.47455;,
 12.47629;-0.00042;6.53043;,
 -0.00000;-0.00042;6.53042;,
 12.47628;0.85197;6.47455;,
 -0.00000;0.85197;6.47455;,
 -0.00000;1.68978;6.30790;,
 -0.00000;2.49866;6.03332;,
 0.00000;3.26479;5.65551;,
 12.47629;3.97505;5.18094;,
 -0.00000;3.97505;5.18093;,
 12.47629;4.61729;4.61770;,
 -0.00000;4.61728;4.61770;,
 12.47629;5.18051;3.97547;,
 0.00000;5.18051;3.97547;,
 0.00000;5.65509;3.26521;,
 0.00000;6.03290;2.49908;,
 0.00000;6.30748;1.69020;,
 12.47629;6.47413;0.85239;,
 0.00000;6.47413;0.85239;;
 
 126;
 3;0,1,2;,
 3;1,3,2;,
 3;2,3,4;,
 3;3,5,4;,
 3;4,5,6;,
 3;5,7,6;,
 3;6,7,8;,
 3;7,9,8;,
 3;8,9,10;,
 3;10,9,11;,
 3;9,12,11;,
 3;12,13,11;,
 3;11,13,14;,
 3;14,13,15;,
 3;13,16,15;,
 3;15,16,17;,
 3;16,18,17;,
 3;17,18,19;,
 3;18,20,19;,
 3;19,20,21;,
 3;20,22,21;,
 3;21,22,23;,
 3;22,24,23;,
 3;24,25,23;,
 3;23,25,26;,
 3;25,27,26;,
 3;26,27,28;,
 3;27,29,28;,
 3;28,29,30;,
 3;29,31,30;,
 3;30,31,32;,
 3;31,33,32;,
 3;32,33,34;,
 3;33,35,34;,
 3;34,35,36;,
 3;35,37,36;,
 3;36,37,38;,
 3;37,39,38;,
 3;38,39,40;,
 3;39,41,40;,
 3;40,41,42;,
 3;41,43,42;,
 3;42,43,44;,
 3;43,45,44;,
 3;44,45,46;,
 3;45,47,46;,
 4;48,49,50,51;,
 3;52,49,20;,
 3;49,48,20;,
 3;48,22,20;,
 4;18,53,52,20;,
 4;16,54,53,18;,
 3;55,54,56;,
 3;54,16,56;,
 3;16,13,56;,
 4;57,58,55,56;,
 4;59,60,58,57;,
 3;61,60,7;,
 3;60,59,7;,
 3;59,9,7;,
 4;5,62,61,7;,
 4;3,63,62,5;,
 3;64,63,65;,
 3;63,3,65;,
 3;3,1,65;,
 4;66,67,64,65;,
 4;68,69,67,66;,
 3;69,68,70;,
 3;70,68,4;,
 3;68,2,4;,
 4;6,71,70,4;,
 4;8,72,71,6;,
 3;72,8,73;,
 3;73,8,74;,
 3;8,10,74;,
 4;75,76,73,74;,
 4;77,78,76,75;,
 3;78,77,79;,
 3;79,77,15;,
 3;77,14,15;,
 4;17,80,79,15;,
 4;19,81,80,17;,
 3;81,19,82;,
 3;82,19,83;,
 3;19,21,83;,
 4;84,85,82,83;,
 4;86,87,85,84;,
 3;26,28,86;,
 3;86,28,87;,
 3;28,88,87;,
 4;30,89,88,28;,
 4;32,90,89,30;,
 3;32,34,90;,
 3;34,91,90;,
 3;91,92,90;,
 4;93,94,92,91;,
 4;95,96,94,93;,
 3;38,40,95;,
 3;40,97,95;,
 3;97,96,95;,
 4;42,98,97,40;,
 4;44,99,98,42;,
 3;44,46,99;,
 3;46,100,99;,
 3;100,101,99;,
 4;102,103,101,100;,
 4;104,105,103,102;,
 3;43,106,45;,
 3;45,106,104;,
 3;106,105,104;,
 4;41,107,106,43;,
 4;39,108,107,41;,
 3;37,109,39;,
 3;39,109,108;,
 3;109,110,108;,
 4;111,112,110,109;,
 4;113,114,112,111;,
 3;31,115,33;,
 3;33,115,113;,
 3;115,114,113;,
 4;29,116,115,31;,
 4;27,117,116,29;,
 3;25,118,27;,
 3;118,119,27;,
 3;119,117,27;,
 4;51,50,119,118;;
 
 MeshMaterialList {
  1;
  126;
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
   0.640000;0.640000;0.640000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  140;
  1.000000;0.000000;-0.000000;,
  1.000000;0.000000;0.000002;,
  1.000000;0.000000;-0.000002;,
  1.000000;-0.000000;0.000001;,
  1.000000;-0.000000;0.000001;,
  1.000000;0.000000;0.000002;,
  1.000000;0.000000;-0.000003;,
  1.000000;0.000000;-0.000001;,
  1.000000;0.000000;0.000006;,
  1.000000;0.000000;-0.000005;,
  1.000000;0.000000;0.000000;,
  1.000000;0.000000;-0.000009;,
  1.000000;0.000000;-0.000027;,
  1.000000;0.000000;-0.000014;,
  1.000000;0.000000;-0.000003;,
  1.000000;0.000000;-0.000001;,
  1.000000;0.000000;0.000008;,
  1.000000;0.000000;-0.000006;,
  1.000000;0.000000;0.000001;,
  1.000000;-0.000000;0.000002;,
  1.000000;-0.000000;-0.000001;,
  1.000000;0.000000;-0.000000;,
  1.000000;0.000000;0.000000;,
  1.000000;-0.000000;-0.000000;,
  1.000000;-0.000000;-0.000001;,
  1.000000;-0.000000;0.000000;,
  1.000000;0.000000;0.000003;,
  1.000000;0.000000;0.000002;,
  1.000000;0.000000;-0.000000;,
  1.000000;0.000000;-0.000000;,
  1.000000;0.000000;-0.000002;,
  1.000000;0.000000;-0.000009;,
  1.000000;0.000000;0.000012;,
  1.000000;0.000000;0.000009;,
  1.000000;0.000000;0.000005;,
  1.000000;0.000000;-0.000012;,
  1.000000;0.000000;0.000004;,
  1.000000;0.000000;-0.000000;,
  1.000000;0.000000;0.000001;,
  1.000000;0.000000;0.000001;,
  1.000000;0.000000;0.000001;,
  1.000000;-0.000000;-0.000001;,
  1.000000;-0.000000;0.000001;,
  1.000000;0.000000;-0.000001;,
  0.000000;1.000000;-0.000001;,
  -0.000000;0.988357;0.152151;,
  -0.000000;0.965926;0.258820;,
  -0.000000;0.923880;0.382683;,
  -0.000000;0.849185;0.528096;,
  -0.000000;0.793352;0.608763;,
  -0.000001;0.707107;0.707106;,
  -0.000001;0.608764;0.793351;,
  -0.000000;0.518795;0.854899;,
  -0.000000;0.382683;0.923880;,
  -0.000000;0.227042;0.973885;,
  -0.000000;0.130529;0.991445;,
  -0.000000;0.000000;1.000000;,
  -0.000000;-0.130529;0.991445;,
  -0.000000;-0.227042;0.973885;,
  -0.000000;-0.382683;0.923880;,
  -0.000000;-0.518795;0.854899;,
  -0.000001;-0.608762;0.793353;,
  -0.000000;-0.707107;0.707107;,
  -0.000000;-0.793353;0.608762;,
  -0.000000;-0.849184;0.528097;,
  -0.000000;-0.923879;0.382684;,
  -0.000000;-0.965926;0.258818;,
  -0.000000;-0.988357;0.152151;,
  -0.000000;-1.000000;-0.000000;,
  0.000000;-0.988357;-0.152152;,
  0.000000;-0.965926;-0.258819;,
  0.000000;-0.923881;-0.382681;,
  0.000000;-0.854898;-0.518796;,
  0.000000;-0.793354;-0.608761;,
  0.000000;-0.707108;-0.707105;,
  -0.000000;-0.591286;-0.806462;,
  0.000000;-0.499999;-0.866026;,
  0.000000;-0.382682;-0.923880;,
  0.000000;-0.237660;-0.971348;,
  0.000000;-0.130528;-0.991445;,
  0.000000;-0.000000;-1.000000;,
  0.000000;0.130528;-0.991445;,
  0.000000;0.237660;-0.971348;,
  0.000000;0.382680;-0.923881;,
  0.000000;0.500004;-0.866023;,
  0.000000;0.591292;-0.806458;,
  0.000000;0.707106;-0.707107;,
  0.000000;0.793354;-0.608761;,
  0.000000;0.854898;-0.518795;,
  0.000000;0.923880;-0.382681;,
  0.000000;0.965928;-0.258812;,
  0.000000;0.988358;-0.152144;,
  -0.000000;0.988357;0.152151;,
  0.000000;0.988358;-0.152144;,
  -0.000000;-0.988357;0.152151;,
  0.000000;-0.988357;-0.152152;,
  0.000000;-0.162932;-0.986637;,
  0.000000;0.162934;-0.986637;,
  -0.000000;0.152152;0.988357;,
  -0.000000;-0.152152;0.988357;,
  -0.000000;0.806461;0.591287;,
  -0.000000;0.582448;0.812868;,
  -0.000000;-0.582447;0.812869;,
  -0.000000;-0.806462;0.591287;,
  0.000000;-0.812867;-0.582449;,
  0.000000;-0.591284;-0.806463;,
  -0.000000;0.591289;-0.806460;,
  0.000000;0.812868;-0.582449;,
  0.000000;0.973887;-0.227033;,
  0.000000;0.980788;-0.195078;,
  0.000000;0.854898;-0.518796;,
  -0.000000;0.831471;-0.555569;,
  -0.000000;0.528101;-0.849181;,
  -0.000001;0.555573;-0.831468;,
  0.000000;0.237661;-0.971348;,
  0.000000;0.195096;-0.980784;,
  0.000000;-0.237661;-0.971348;,
  0.000000;-0.195094;-0.980785;,
  0.000000;-0.528095;-0.849186;,
  0.000001;-0.555566;-0.831472;,
  0.000000;-0.854898;-0.518797;,
  0.000000;-0.831469;-0.555571;,
  0.000000;-0.973885;-0.227043;,
  -0.000000;-0.980785;-0.195092;,
  -0.000000;-0.980785;0.195090;,
  -0.000000;-0.973885;0.227041;,
  -0.000000;-0.866025;0.500001;,
  -0.000000;-0.831471;0.555569;,
  0.000000;-0.555566;0.831473;,
  -0.000000;-0.518793;0.854900;,
  -0.000000;-0.258818;0.965926;,
  -0.000001;-0.195089;0.980786;,
  -0.000000;0.258818;0.965926;,
  -0.000001;0.195089;0.980786;,
  -0.000000;0.518793;0.854900;,
  0.000000;0.555566;0.831473;,
  -0.000000;0.866026;0.499998;,
  -0.000000;0.831471;0.555569;,
  -0.000000;0.973885;0.227042;,
  -0.000000;0.980785;0.195090;;
  126;
  3;10,33,32;,
  3;33,34,32;,
  3;32,34,31;,
  3;34,35,31;,
  3;31,35,30;,
  3;35,36,30;,
  3;30,36,29;,
  3;36,37,29;,
  3;29,37,28;,
  3;28,37,27;,
  3;37,38,27;,
  3;38,39,27;,
  3;27,39,10;,
  3;10,39,26;,
  3;39,40,26;,
  3;26,40,25;,
  3;40,41,25;,
  3;25,41,24;,
  3;41,42,24;,
  3;24,42,23;,
  3;42,43,23;,
  3;23,43,22;,
  3;43,0,22;,
  3;0,1,22;,
  3;22,1,21;,
  3;1,2,21;,
  3;21,2,20;,
  3;2,3,20;,
  3;20,3,19;,
  3;3,4,19;,
  3;19,4,10;,
  3;4,5,10;,
  3;10,5,18;,
  3;5,6,18;,
  3;18,6,17;,
  3;6,7,17;,
  3;17,7,16;,
  3;7,8,16;,
  3;16,8,15;,
  3;8,9,15;,
  3;15,9,14;,
  3;9,10,14;,
  3;14,10,10;,
  3;10,11,10;,
  3;10,11,13;,
  3;11,12,13;,
  4;93,91,44,44;,
  3;90,91,108;,
  3;91,93,108;,
  3;93,109,108;,
  4;89,89,90,108;,
  4;110,88,89,89;,
  3;87,88,107;,
  3;88,110,107;,
  3;110,111,107;,
  4;86,86,87,107;,
  4;106,85,86,86;,
  3;84,85,112;,
  3;85,106,112;,
  3;106,113,112;,
  4;83,83,84,112;,
  4;114,82,83,83;,
  3;81,82,97;,
  3;82,114,97;,
  3;114,115,97;,
  4;80,80,81,97;,
  4;96,79,80,80;,
  3;79,96,78;,
  3;78,96,116;,
  3;96,117,116;,
  4;77,77,78,116;,
  4;118,76,77,77;,
  3;76,118,75;,
  3;75,118,105;,
  3;118,119,105;,
  4;74,74,75,105;,
  4;104,73,74,74;,
  3;73,104,72;,
  3;72,104,120;,
  3;104,121,120;,
  4;71,71,72,120;,
  4;122,70,71,71;,
  3;70,122,69;,
  3;69,122,95;,
  3;122,123,95;,
  4;68,68,69,95;,
  4;94,67,68,68;,
  3;124,125,94;,
  3;94,125,67;,
  3;125,66,67;,
  4;65,65,66,125;,
  4;126,64,65,65;,
  3;126,127,64;,
  3;127,103,64;,
  3;103,63,64;,
  4;62,62,63,103;,
  4;102,61,62,62;,
  3;128,129,102;,
  3;129,60,102;,
  3;60,61,102;,
  4;59,59,60,129;,
  4;130,58,59,59;,
  3;130,131,58;,
  3;131,99,58;,
  3;99,57,58;,
  4;56,56,57,99;,
  4;98,55,56,56;,
  3;132,54,133;,
  3;133,54,98;,
  3;54,55,98;,
  4;53,53,54,132;,
  4;134,52,53,53;,
  3;135,101,134;,
  3;134,101,52;,
  3;101,51,52;,
  4;50,50,51,101;,
  4;100,49,50,50;,
  3;136,48,137;,
  3;137,48,100;,
  3;48,49,100;,
  4;47,47,48,136;,
  4;138,46,47,47;,
  3;139,92,138;,
  3;92,45,138;,
  3;45,46,138;,
  4;44,44,45,92;;
 }
 MeshTextureCoords {
  120;
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;;
 }
 MeshVertexColors {
  120;
  0;1.000000;1.000000;1.000000;1.000000;,
  1;1.000000;1.000000;1.000000;1.000000;,
  2;1.000000;1.000000;1.000000;1.000000;,
  3;1.000000;1.000000;1.000000;1.000000;,
  4;1.000000;1.000000;1.000000;1.000000;,
  5;1.000000;1.000000;1.000000;1.000000;,
  6;1.000000;1.000000;1.000000;1.000000;,
  7;1.000000;1.000000;1.000000;1.000000;,
  8;1.000000;1.000000;1.000000;1.000000;,
  9;1.000000;1.000000;1.000000;1.000000;,
  10;1.000000;1.000000;1.000000;1.000000;,
  11;1.000000;1.000000;1.000000;1.000000;,
  12;1.000000;1.000000;1.000000;1.000000;,
  13;1.000000;1.000000;1.000000;1.000000;,
  14;1.000000;1.000000;1.000000;1.000000;,
  15;1.000000;1.000000;1.000000;1.000000;,
  16;1.000000;1.000000;1.000000;1.000000;,
  17;1.000000;1.000000;1.000000;1.000000;,
  18;1.000000;1.000000;1.000000;1.000000;,
  19;1.000000;1.000000;1.000000;1.000000;,
  20;1.000000;1.000000;1.000000;1.000000;,
  21;1.000000;1.000000;1.000000;1.000000;,
  22;1.000000;1.000000;1.000000;1.000000;,
  23;1.000000;1.000000;1.000000;1.000000;,
  24;1.000000;1.000000;1.000000;1.000000;,
  25;1.000000;1.000000;1.000000;1.000000;,
  26;1.000000;1.000000;1.000000;1.000000;,
  27;1.000000;1.000000;1.000000;1.000000;,
  28;1.000000;1.000000;1.000000;1.000000;,
  29;1.000000;1.000000;1.000000;1.000000;,
  30;1.000000;1.000000;1.000000;1.000000;,
  31;1.000000;1.000000;1.000000;1.000000;,
  32;1.000000;1.000000;1.000000;1.000000;,
  33;1.000000;1.000000;1.000000;1.000000;,
  34;1.000000;1.000000;1.000000;1.000000;,
  35;1.000000;1.000000;1.000000;1.000000;,
  36;1.000000;1.000000;1.000000;1.000000;,
  37;1.000000;1.000000;1.000000;1.000000;,
  38;1.000000;1.000000;1.000000;1.000000;,
  39;1.000000;1.000000;1.000000;1.000000;,
  40;1.000000;1.000000;1.000000;1.000000;,
  41;1.000000;1.000000;1.000000;1.000000;,
  42;1.000000;1.000000;1.000000;1.000000;,
  43;1.000000;1.000000;1.000000;1.000000;,
  44;1.000000;1.000000;1.000000;1.000000;,
  45;1.000000;1.000000;1.000000;1.000000;,
  46;1.000000;1.000000;1.000000;1.000000;,
  47;1.000000;1.000000;1.000000;1.000000;,
  48;1.000000;1.000000;1.000000;1.000000;,
  49;1.000000;1.000000;1.000000;1.000000;,
  50;1.000000;1.000000;1.000000;1.000000;,
  51;1.000000;1.000000;1.000000;1.000000;,
  52;1.000000;1.000000;1.000000;1.000000;,
  53;1.000000;1.000000;1.000000;1.000000;,
  54;1.000000;1.000000;1.000000;1.000000;,
  55;1.000000;1.000000;1.000000;1.000000;,
  56;1.000000;1.000000;1.000000;1.000000;,
  57;1.000000;1.000000;1.000000;1.000000;,
  58;1.000000;1.000000;1.000000;1.000000;,
  59;1.000000;1.000000;1.000000;1.000000;,
  60;1.000000;1.000000;1.000000;1.000000;,
  61;1.000000;1.000000;1.000000;1.000000;,
  62;1.000000;1.000000;1.000000;1.000000;,
  63;1.000000;1.000000;1.000000;1.000000;,
  64;1.000000;1.000000;1.000000;1.000000;,
  65;1.000000;1.000000;1.000000;1.000000;,
  66;1.000000;1.000000;1.000000;1.000000;,
  67;1.000000;1.000000;1.000000;1.000000;,
  68;1.000000;1.000000;1.000000;1.000000;,
  69;1.000000;1.000000;1.000000;1.000000;,
  70;1.000000;1.000000;1.000000;1.000000;,
  71;1.000000;1.000000;1.000000;1.000000;,
  72;1.000000;1.000000;1.000000;1.000000;,
  73;1.000000;1.000000;1.000000;1.000000;,
  74;1.000000;1.000000;1.000000;1.000000;,
  75;1.000000;1.000000;1.000000;1.000000;,
  76;1.000000;1.000000;1.000000;1.000000;,
  77;1.000000;1.000000;1.000000;1.000000;,
  78;1.000000;1.000000;1.000000;1.000000;,
  79;1.000000;1.000000;1.000000;1.000000;,
  80;1.000000;1.000000;1.000000;1.000000;,
  81;1.000000;1.000000;1.000000;1.000000;,
  82;1.000000;1.000000;1.000000;1.000000;,
  83;1.000000;1.000000;1.000000;1.000000;,
  84;1.000000;1.000000;1.000000;1.000000;,
  85;1.000000;1.000000;1.000000;1.000000;,
  86;1.000000;1.000000;1.000000;1.000000;,
  87;1.000000;1.000000;1.000000;1.000000;,
  88;1.000000;1.000000;1.000000;1.000000;,
  89;1.000000;1.000000;1.000000;1.000000;,
  90;1.000000;1.000000;1.000000;1.000000;,
  91;1.000000;1.000000;1.000000;1.000000;,
  92;1.000000;1.000000;1.000000;1.000000;,
  93;1.000000;1.000000;1.000000;1.000000;,
  94;1.000000;1.000000;1.000000;1.000000;,
  95;1.000000;1.000000;1.000000;1.000000;,
  96;1.000000;1.000000;1.000000;1.000000;,
  97;1.000000;1.000000;1.000000;1.000000;,
  98;1.000000;1.000000;1.000000;1.000000;,
  99;1.000000;1.000000;1.000000;1.000000;,
  100;1.000000;1.000000;1.000000;1.000000;,
  101;1.000000;1.000000;1.000000;1.000000;,
  102;1.000000;1.000000;1.000000;1.000000;,
  103;1.000000;1.000000;1.000000;1.000000;,
  104;1.000000;1.000000;1.000000;1.000000;,
  105;1.000000;1.000000;1.000000;1.000000;,
  106;1.000000;1.000000;1.000000;1.000000;,
  107;1.000000;1.000000;1.000000;1.000000;,
  108;1.000000;1.000000;1.000000;1.000000;,
  109;1.000000;1.000000;1.000000;1.000000;,
  110;1.000000;1.000000;1.000000;1.000000;,
  111;1.000000;1.000000;1.000000;1.000000;,
  112;1.000000;1.000000;1.000000;1.000000;,
  113;1.000000;1.000000;1.000000;1.000000;,
  114;1.000000;1.000000;1.000000;1.000000;,
  115;1.000000;1.000000;1.000000;1.000000;,
  116;1.000000;1.000000;1.000000;1.000000;,
  117;1.000000;1.000000;1.000000;1.000000;,
  118;1.000000;1.000000;1.000000;1.000000;,
  119;1.000000;1.000000;1.000000;1.000000;;
 }
}