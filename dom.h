
#ifndef DOM_H
#define DOM_H

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

typedef enum {
    NONE,
    INLINE,
    BLOCK,
    INLINE_BLOCK

}StyleDisplay;

typedef enum {
    STATIC,
    RELATIVE,
    FIXED,
    ABSOLUTE,
    STICKY
}PositionPropery;

typedef struct Style {
    StyleDisplay display;
    float width;
    float height;
    float margin[4]; // 0 TOP, 1 DOWN, 2 LEFT, 3 RIGHT
    float padding[4]; // 0 TOP, 1 DOWN, 2 LEFT, 3 RIGHT
    char* color;
    char* background_color;
    float font_size;

}Style;

// Function prototype
node* create_node(NodeType type);

#endif