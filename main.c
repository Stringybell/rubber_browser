#include "stdlib.h"
#include "stdio.h"
#include "string.h"

typedef enum{
TAG_NODE, // 0: Represents HTML tags such as <div>, <img>, <a>...
TEXT_NODE, // 1: Represents text
COMMENT_NODE // 2: Parses text without printing it
} NodeType;

/*
 * Represents the Metadata of the HTML object
 * and stores it in a linked list
 */
typedef struct Attribute{
	char* type; //e.g. "src","href", "width"
	char* value;  //e.g. "image.png"
	struct Attribute* next;
} Attribute;

/*
 * Represents the DOM
 *
 */
typedef struct Node{
	NodeType type;
	char* tag_name; //html tag, ex. <div>
	char* text_content;
	Attribute* attribute;
	struct Node* child;
	struct Node* next_sibling;
	struct Style* style;

} node ;
