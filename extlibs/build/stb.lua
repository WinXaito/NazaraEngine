LIBRARY.Name = "stb_image"

LIBRARY.Defines = {
	"STBI_NO_STDIO"
}

LIBRARY.Flags = {
	"EnableSSE2"
}

LIBRARY.Language = "C++" -- On compile en C++ car le C99 n'est pas support� partout

LIBRARY.Files = {
	"../extlibs/include/stb/*.h",
	"../extlibs/src/stb/*.cpp"
}
