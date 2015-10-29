file(GLOB GUI_SRCS *.cpp *.h)
set(GUI_SRCS ${GUI_SRCS} PARENT_SCOPE)

source_group("gui" FILES ${GUI_SRCS})