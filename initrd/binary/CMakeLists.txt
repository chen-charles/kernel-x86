file(GLOB binaries
	"*"
)

file(GLOB liExcludes "CMakeLists.txt")
list(REMOVE_ITEM binaries ${liExcludes})

file(COPY ${binaries} DESTINATION ${EXECUTABLE_OUTPUT_PATH})
