#include <iostream>
#define NEW '\n'
#include <iostream>
#define NEW '\n'
#define TAB '\t'
#define RET '\r'
#define OPEN '<'
#define EXCLAMATION '!'
#define MINUS '-'
#define CLOSE '>'
#define SLASH '/'
#define QM '?'
#define SPACE ' '
#define EQUAL '='
#define QUOTE '"'
#define DQUOTE '"'
#include <cstdlib>
#include <new>
#include <fstream>
#include<wchar.h>
#include<string.h>
#include<queue>
#include<wchar.h>
#include<string.h>
#include<queue>
#include <cairo.h>
#include <gtk/gtk.h>
#include<cstdlib>
#include <cstring>
#include <string>

using namespace std;

void on_window_destroy (GtkWidget *widget, gpointer data)
{
  gtk_main_quit ();
}
static void do_drawing(cairo_t *);
using namespace std;

//GLOBAL VARIABLES DECLARATION....................................................................................
ofstream out;
int add_flag=0;
char *a1;
int add_a=50;
int add_b=50;
int add_c=150;
int add_d=50;
char *n1;
char *v1;
size_t  STRING_LENGTH = 256;
char *EMPTY_STRING = "";
int global_count=0;
int ht_g;
int width_g;
int max_child=0;
int cut_x=0;
int cut_y=0;
int cut_flag=0;
int marker=0;

std::string attribute;

struct XMLAttribute {
                    char *name;
                    char *value;

                    /* the linke to the next element in the list */
                    XMLAttribute *next;
                };

struct XMLElement {
                char *name;
                char *value;

                XMLAttribute *attributes;

                /* the link to the parent element in the list */
                XMLElement *parent;
                /* the link to the next child element in the list */
                XMLElement *elements;

                /* the link to the next element in the list */
                XMLElement *next;
                int distance;
                int y;
                int test_c;
                int update;
                int a;
                int b;
                int c;
                int d;

            long character_number;
            };

struct XMLDocument {
              XMLElement *elements;
                     };

struct XMLDocument *Doc=NULL;
struct XMLElement *cut=NULL;
struct XMLElement *cutf=NULL;

//WRITING BACK TO FILE FUNC..........................................................................................
void write_file(struct XMLElement *root,struct XMLElement *Temp)
{

    if(Temp!=NULL && root==Temp)
    {
        root->value=Temp->value;
        root->name=Temp->name;
    }
    if(root==NULL) return;
    struct XMLElement* temp;
    struct XMLAttribute* temp_a;
    out<<endl<<"<"<<root->name;
    temp_a=root->attributes;


    while(temp_a!=NULL)
    {
        out<<" "<<temp_a->name<<"="<<"\"";
        out<<temp_a->value<<"\"";
        temp_a=temp_a->next;
    }
    temp=root;
    out<<">";
    out<<root->value;
    root=root->elements;
    while(root!=NULL)
    {
        write_file(root,Temp);
        root=root->next;
    }
    out<<"</"<<temp->name<<">"<<endl;

}

// CLASS BEGINS...................................................................................................
class tree{

    public:

        struct XMLDocument  *document;
        struct XMLAttribute *attribute;
        struct XMLElement   *element;
        struct XMLElement   *element_t;
        char *file_string;
        int     index;
        char character,test_char;
        char delim;
        bool    inside_flag;
        char *element_name;
        char *element_value;
        char *attribute_name;
        char *attribute_value;
        char *verifier;

           long character_number;

public:
struct XMLDocument *installer_xml_document_new()
{
    struct XMLDocument *doc_t;
    doc_t=(struct XMLDocument*)calloc(1,sizeof(struct XMLDocument));
    return doc_t;
};
struct XMLElement *installer_xml_element_new(char *e_name,char *e_value)
{
    struct XMLElement *ele_t;
    ele_t=(struct XMLElement*)calloc(1,sizeof(struct XMLElement));
    ele_t->name   = (char*) calloc(STRING_LENGTH, sizeof(char));
    ele_t->name=strcpy(ele_t->name,e_name);
    ele_t->value   = (char*) calloc(STRING_LENGTH, sizeof(char));
    ele_t->value=strcpy(ele_t->value,e_value);
    return ele_t;
};
int element_name_validity(char *str)
{
   int i=0;
   char ch;
   if(str[0]==88 || str[0]==120)
     { if(str[1]==77 || str[1]==109)
         { if(str[2]==76 || str[2]==108)
                 {return 0;
                 }
          }
      }
    if((str[0]>91 && str[0] <97) || str[0]<65 || str[0]>122)
    {return 0;
       }
    while (i < strlen(str))
          {
          ch = str[i];
          if(ch == 32)
          {
              return 0;
              }
              i++;
              }
              return 1;

};
struct XMLElement *installer_xml_element_add_element(struct XMLElement *element, struct XMLElement *element_t)
        {
            {
            element_t->next=element->elements;
            element_t->parent=element;
            element->elements=element_t;
            return element_t;
            }
        };

struct XMLElement *installer_xml_document_add_element(struct XMLDocument *document, struct XMLElement *element_t)
{
    document->elements=element_t;
    return(document->elements);
};


        void installer_xml_element_delete(struct XMLElement *element_t)
        {
            element_t=NULL;
        };

        void _installer_xml_reader_append_character(char *attribute_name, char character)
        {
            //int length=strlen(attribute_name)+1;
            //attribute_name=(char *)realloc(attribute_name,length*sizeof(char));
            if(character!=NEW)
            attribute_name=strcat(attribute_name,&character);
        };
        struct XMLElement *installer_xml_element_get_parent(struct XMLElement *element)
        {
            if(element==NULL)
                return NULL;
            else
                return element->parent;
        };
        char *installer_xml_element_get_name(struct XMLElement *element)
        {
            return element->name;
        };
        void installer_xml_element_set_name(struct XMLElement *element, char *element_name)
        {

            element->name=element_name;
        };
        void installer_xml_element_set_value(struct XMLElement *element, char *element_value)
        {
            element->value=element_value;
        };
        void dispparser();

        struct XMLAttribute *installer_xml_attribute_new(char *attribute_name,char *attribute_value)
        {
            struct XMLAttribute *attribute_temp=(struct XMLAttribute *)calloc(1,sizeof(struct XMLAttribute));
            attribute_temp->name   = attribute_name;
            attribute_temp->value   = attribute_value;
            return attribute_temp;
        };

        void installer_xml_element_add_attribute(struct XMLElement *element, struct XMLAttribute *attribute)
        {
            attribute->next=element->attributes;
            element->attributes=attribute;

        };

        void installer_xml_attribute_delete(struct XMLAttribute *attribute)
        {
            attribute=NULL;
        };


    tree(char *str,size_t s){
    int line_count=0;
    file_string = str;
    document  = installer_xml_document_new();
    attribute = NULL;
    element   = NULL;
    element_t = NULL;     /* temporaary element */

    /* xml string to parse */

    index           = 0;        /* first level cursor */
    character       = WEOF;
    delim           = WEOF;
    inside_flag     = false;

    element_name   = (char*) calloc(STRING_LENGTH, sizeof(char));
    element_value  = (char*) calloc(STRING_LENGTH, sizeof(char));
    attribute_name = (char*) calloc(STRING_LENGTH, sizeof(char));
    attribute_value= (char*) calloc(STRING_LENGTH, sizeof(char));
    verifier       = (char*) calloc(STRING_LENGTH, sizeof(char));

    character_number=s;



    element_t = installer_xml_element_new("XML DOCUMENT", "v1.0");
    //element_t= (struct XMLElement *)calloc(1,struct XMLElement);
    element   = installer_xml_document_add_element(document, element_t);
    element_t=NULL;
    //installer_xml_element_delete(element_t);

    element_t = installer_xml_element_new(EMPTY_STRING, EMPTY_STRING);
    element   = installer_xml_element_add_element(element, element_t);
    //installer_xml_element_delete(element_t);
    element_t=NULL;
    while (index < character_number)
        {
        character = file_string[index];

        //cout << index << "   " << character << '\n';

        if ((character == NEW) || (character == TAB) || (character == RET))
            {
                if(character==NEW) line_count++;
                index++;
                continue;
            }
        if (character == OPEN)
            {
            /* comment section */
            if ((file_string[index + 1] == EXCLAMATION) && (file_string[index + 2] == MINUS) && (file_string[index + 3] == MINUS))
                {
                    memset(attribute_value, 0, STRING_LENGTH * sizeof(char));
                    index += 4;
                    character = file_string[index];
                    while (!((file_string[index] == MINUS) && (file_string[index + 1] == MINUS) && (file_string[index + 2] == CLOSE)))
                        {
                            _installer_xml_reader_append_character(attribute_name,character);
                            character = file_string[++index];
                        }
                    index += 3;

                /*
                 * comments will not be added to xml structure
                 */
                    continue;
                }


            /* closing tag for the last opened element */
            memset(element_name, 0, STRING_LENGTH * sizeof(char));
            if (file_string[index + 1] == SLASH)
                {
                    memset(verifier, 0, STRING_LENGTH * sizeof(char));
                /* element = element->parent */

                    index=index+2;

                    while (file_string[index] != CLOSE)
                        {
                            test_char=file_string[index];
                            _installer_xml_reader_append_character(verifier, test_char);
                            index++;
                        }

                    index++;
                    if (strcmp(installer_xml_element_get_name(element), verifier) != 0)
                    {
                        cout<<endl<<endl<<"ERROR in line "<<line_count+1<<" - "<<installer_xml_element_get_name(element)<<" should be closed first but -"<<verifier<<" - has been closed first instead."<<endl;
                        marker=1;
                    }
                    element = installer_xml_element_get_parent(element);
                    continue;
                }


            if (file_string[index + 1] == QM)
                {
                    character = file_string[++index];
                    inside_flag = true;
                }

            /* create a new element */
            character = file_string[++index];
            while ((character != SLASH) && (character != SPACE) && (character != CLOSE))
                {
                    if(character==NEW) line_count++;
                /* going until the element name has been entirely read */
                    if ((character != NEW)&& (character != TAB)&&(character != RET))
                    {
                        _installer_xml_reader_append_character(element_name, character);
                    }

                    character = file_string[++index];
                }



                        /* element has been seted, going to the child element */
                if (strcmp(installer_xml_element_get_name(element), EMPTY_STRING) != 0)
                    {
                                /* element = element->child */
                        //element_t=(struct XMLElement *)calloc(1,sizeof(struct XMLElement));
                        element_t = installer_xml_element_new(EMPTY_STRING, EMPTY_STRING);
                        element   = installer_xml_element_add_element(element, element_t);
                        element_t=NULL;
                        //installer_xml_element_delete(element_t);
                    }
            if(element_name_validity(element_name)==0 && inside_flag==false )
            {
                cout << "Invalid element name in line "<<line_count+1<<" - "<<element_name;
                marker=1;
            }
            /* element->name = element_name */
                installer_xml_element_set_name(element, element_name);
                element_name   = (char*) calloc(STRING_LENGTH, sizeof(char));
                //cout<<element->name<<endl;
                while (character == SPACE)
                    {
                        character = file_string[++index];
                        if (character == SLASH)
                        {
                            break;
                        }

                        if ((character == QM) && (inside_flag == true))
                        {
                            break;
                        }

                        memset(attribute_name,  0, STRING_LENGTH * sizeof(char));
                        memset(attribute_value, 0, STRING_LENGTH * sizeof(char));
                        /* going until the attribute name has been entirely read */
                        while (character != EQUAL)
                            {
                                if (character==NEW) line_count++;
                                if ((character != NEW)&& (character != TAB)&& (character != RET))
                                {
                                    _installer_xml_reader_append_character(attribute_name,character);
                                }

                                character = file_string[++index];
                            }

                            character = file_string[++index];
                            if ((character == QUOTE) || (character == DQUOTE))
                                {
                                    delim     = character;
                                    character = file_string[++index];
                                }

                            /* going until the attribute value has been entirely read */
                            while ((character != delim) && (delim != WEOF))
                            {
                                if(character==NEW) line_count++;
                                if ((character != NEW)&& (character != TAB)&& (character != RET))
                                    {
                                        _installer_xml_reader_append_character(attribute_value,character);
                                    }

                                character = file_string[++index];
                            }

                            delim     = WEOF;
                            character = file_string[++index];
                            if(element_name_validity(attribute_name)==0 && inside_flag==false )
            {
                cout << "Invalid attribute name in line "<<line_count+1<<" - "<<attribute_name;
                marker=1;
            }
                            attribute = installer_xml_attribute_new(attribute_name,attribute_value);
                            attribute->next=element->attributes;
                            element->attributes=attribute;
                            //installer_xml_element_add_attribute(element, attribute);
                            //cout<<endl;
                            //cout<<element->attributes->name<<"   "<<element->attributes->value<<endl;
                            attribute_name=(char*) calloc(STRING_LENGTH, sizeof(char));
                            attribute_value=(char*) calloc(STRING_LENGTH, sizeof(char));
                            //installer_xml_attribute_delete(attribute);
                            attribute=NULL;
                            //cout<<element->attributes->name<<endl;
                }

                if (character == SLASH)
                    {
                    /* element = element->parent */
                        element = installer_xml_element_get_parent(element);
                        character = file_string[++index];
                        while (character != CLOSE)
                            {
                                character = file_string[++index];
                            }
                    }

                    /* first xml element end <?xml version="1.0" encoding="UTF-8"?> */
                    if ((character == QM) && (inside_flag == true))
                        {
                        /* element = element->parent - parent is NULL for the first element */
                        element = installer_xml_element_get_parent(element);
                        character   = file_string[++index];
                        inside_flag = false;
                        while (character != CLOSE)
                            {
                                character = file_string[++index];
                            }
                        }
        }



        /* element has a value */
        if ((character != OPEN) && (character != CLOSE) && (character != SLASH) && (character != SPACE))
            {
                memset(element_value,  0, STRING_LENGTH * sizeof(char));

                while (character != OPEN)
                    {
                        if (character==NEW) line_count++;
                        if ((character != NEW)&& (character != TAB)&& (character != RET))
                        {
                            _installer_xml_reader_append_character(element_value,character);
                        }

                        character = file_string[++index];
                    }

                /* element->value = element_value */
                installer_xml_element_set_value(element, element_value);
                element_value   = (char*) calloc(STRING_LENGTH, sizeof(char));
                continue;
            }

        index++;
    }

    document->elements=reverse_tree(document->elements);
    display();
    Doc=document;

}


    void reverse_fn(struct XMLElement ** head_ref)
{
    struct XMLElement* first;
    struct XMLElement* rest;
  /* empty list */
    if (*head_ref == NULL)
       return;

   /* suppose first = {1, 2, 3}, rest = {2, 3} */

    first = *head_ref;
    rest  = first->next;
   /* List has only one node */
    if (rest == NULL)
       return;
    /* reverse the rest list and put the first element at the end */
    reverse_fn(&rest);
    first->next->next  = first;
   /* tricky step -- see the diagram */
    first->next  = NULL;
    /* fix the head pointer */
    *head_ref = rest;
}
    void reverse_at_fn(struct XMLAttribute** head_ref)
{   struct XMLAttribute* first;
    struct XMLAttribute* rest;
    /* empty list */

    if (*head_ref == NULL)
       return;

  /* suppose first = {1, 2, 3}, rest = {2, 3} */

    first = *head_ref;

    rest  = first->next;



    /* List has only one node */

    if (rest == NULL)

       return;

   /* reverse the rest list and put the first element at the end */

    reverse_at_fn(&rest);

    first->next->next  = first;

   /* tricky step -- see the diagram */

    first->next  = NULL;

   /* fix the head pointer */

    *head_ref = rest;

}

    struct XMLElement *reverse_tree(struct XMLElement *root)
    {
        if (root==NULL) return NULL;
        reverse_fn(&root);
        struct XMLElement *temp=root;
        while(temp!=NULL)
        {
          temp->elements=reverse_tree(temp->elements);
          temp=temp->next;
        }

        reverse_at_fn(&(root->attributes));
        return root;
    };

    void display()
    {
        traverse(document->elements);
        global_count=1;
        number_leaves(document->elements);
        decide_width(document->elements);

    }

void number_leaves(struct XMLElement *root)
{
    if (root==NULL) return;
    if (root->elements==NULL)
    {
        root->y=global_count++;
        return;
    }
    root=root->elements;
    while(root!=NULL)
    {
        number_leaves(root);
        root=root->next;
    }
}


int decide_width(struct XMLElement *root)
{
    if(root==NULL) return 0;
   struct XMLElement *temp=NULL;
   temp=root->elements;
   if(temp==NULL)
       return root->y;
   int wide=decide_width(temp);
   while(temp->next!=NULL)
   {
       decide_width(temp);
       temp=temp->next;
   }
   wide=(wide+decide_width(temp)+1)/2;
   root->y=wide;
   return wide;
}

    void traverse(XMLElement *root)
    {
        int width=0,temp_width=0;
        struct XMLElement *node,*trvel;
        queue<struct XMLElement*> level_order;
        struct XMLAttribute *attr=NULL;
        struct XMLElement *nouse=NULL;
        int dist=0,list_len=0;
        int curr_dist=0;
        struct XMLElement* p_check=NULL;
        p_check=root->parent;
        root->distance=0;
        level_order.push(root);
        while(!level_order.empty())
        {

                node=level_order.front();
                level_order.pop();
                curr_dist=node->distance;
                if(dist==curr_dist)
                    {
                        temp_width++;
                        node->y=temp_width;
                    }

                if(dist!=curr_dist)
                {
                    if(temp_width>width)
                        {
                            width=temp_width;
                        }

                    temp_width=1;
                    dist=curr_dist;
                }
                if(node->test_c==-1) continue;
                if(p_check!=node->parent)
                {
                    p_check=node->parent;
                }
                attr=node->attributes;
                while(attr!=NULL)
                {
                    attr=attr->next;
                }

                if(node->elements==NULL )
                {
                    nouse=(struct XMLElement*)calloc(1,sizeof(struct XMLElement));
                    nouse->distance=dist+1;
                    nouse->test_c=-1;
                    level_order.push(nouse);

                }
                if(node==NULL || node->elements==NULL) continue;
                node=node->elements;
                list_len=0;
                while(node!=NULL)
                {
                    list_len++;
                    node->distance=dist+1;
                    level_order.push(node);
                    node=node->next;
                }
                if (list_len>max_child)
                    max_child=list_len;

        }

        ht_g=dist;
        width_g=width;

    }
};


char *getValueAttr(char *a_name,struct XMLElement *node_ptr)
{
    struct XMLAttribute *attr=NULL;
    if(node_ptr==NULL)
        return NULL;
    else
    {
        attr=node_ptr->attributes;
        while(attr!=NULL)
        {
            if(strcmp(a_name,attr->name)==0)
                return attr->value;
            else
                attr=attr->next;
        }
        return NULL;
    }
};

struct XMLElement *getChildElement(char *p_name)
{
        struct XMLElement *node,*trvel, *root;
        root=Doc->elements;
        queue<struct XMLElement*> level_order;
        struct XMLAttribute *attr=NULL;
        struct XMLElement* p_check=NULL;
        level_order.push(root);
       while(!level_order.empty())
        {
            //cout<<"search progressing"<<endl;
                node=level_order.front();
                level_order.pop();
                if(strcmp(p_name,node->name)==0)
                {
                    return node->elements;
                }
                node=node->elements;
                while(node!=NULL)
                {
                    level_order.push(node);
                    node=node->next;
                }


        }
        return NULL;

};

void getNodeContent(struct XMLElement* node)
{
    struct XMLAttribute *attr=NULL;
    if(node==NULL)
        return;
    else
    {
        cout<<"-------------------------------"<<endl;
        cout<<"Name : "<<node->name<<endl;
        cout<<"Value : "<<node->value<<endl;
        attr=node->attributes;
        cout<<"Attributes : "<<endl;
        while(attr!=NULL)
        {
            cout<<"\t"<<attr->name<<"\t: "<<"\""<<attr->value<<"\""<<endl;
            attr=attr->next;
        }

        cout<<"----------------------------------"<<endl;
    }
}
void traverse(XMLElement *root)
    {

        int width=0,temp_width=0;
        struct XMLElement *node,*trvel;
        queue<struct XMLElement*> level_order;
        struct XMLAttribute *attr=NULL;
        struct XMLElement *nouse=NULL;
        int dist=0,list_len=0;
        int curr_dist=0;
        struct XMLElement* p_check=NULL;
        p_check=root->parent;
        root->distance=0;
        level_order.push(root);
        while(!level_order.empty())
        {

                node=level_order.front();
                level_order.pop();
                curr_dist=node->distance;
                if(dist==curr_dist)
                    {
                        temp_width++;
                        node->y=temp_width;
                    }

                if(dist!=curr_dist)
                {

                    //cout<<endl<<endl<<"LEVEL "<<curr_dist<<endl;

                    if(temp_width>width)
                        {
                            width=temp_width;

                        }

                    temp_width=1;
                    dist=curr_dist;
                }
                if(node->test_c==-1) continue;
                if(p_check!=node->parent)
                {

                    p_check=node->parent;
                }
                //cout<<node->name<<":"<<node->value;
                attr=node->attributes;
                //cout<<"  (";
                while(attr!=NULL)
                {
                    //cout<<attr->name<<":"<<attr->value<<",";
                    attr=attr->next;
                }
                //cout<<")  ";
                if(node->elements==NULL )
                {
                    nouse=(struct XMLElement*)calloc(1,sizeof(struct XMLElement));
                    nouse->distance=dist+1;
                    nouse->test_c=-1;
                    level_order.push(nouse);

                }
                if(node==NULL || node->elements==NULL) continue;
                node=node->elements;
                list_len=0;
                while(node!=NULL)
                {
                    list_len++;
                    node->distance=dist+1;
                    level_order.push(node);
                    node=node->next;
                }
                if (list_len>max_child)
                    max_child=list_len;

        }

        ht_g=dist;
        width_g=width;

    }



struct {
  int count;
  double coordx[100];
  double coordy[100];
} glob;

static gboolean on_draw_event(GtkWidget *widget, cairo_t *cr, gpointer user_data)
{
  do_drawing(cr);

  return FALSE;
}

static void do_drawing(cairo_t *cr)
{
  cairo_set_source_rgb(cr, 0, 0, 0);
  cairo_set_line_width(cr, 0.5);

FILE   *stream;

   char wc;
   size_t i=0;

streampos size,end;
stream = fopen("note.xml", "r");
ifstream file("note.xml",ios::in | ios::binary);

  while((getc(stream)!='\n'))
  {
      file.seekg (0, ios::end);
  }
  end = file.tellg();
  size=end;

  file.close();
   char *memblock=(char*) calloc(size, sizeof(char));

   while (EOF != (wc = getc(stream)))
      {
       memblock[i]=wc;
       i++;
      }

      //cout << memblock;
      //cout<<i;

   tree ob(memblock,i);

        int xwidth=200;
        int ywidth=300;
        int x0=xwidth/2;
        int y0=ywidth/2;
        cairo_set_source_rgb(cr, 0, 0, 0);
        cairo_set_line_width(cr, 0.5);

        struct XMLElement *node,*trvel, *root;
        root=ob.document->elements;
        queue<struct XMLElement*> level_order;
        struct XMLAttribute *attr=NULL;
        struct XMLElement* p_check=NULL;
        p_check=root->parent;
        root->distance=0;
        level_order.push(root);
        cairo_set_source_rgb(cr, 238, 180, 34);
        cairo_rectangle(cr, add_a, add_b, add_c, add_d);
        cairo_fill(cr);
        cairo_set_source_rgb(cr, 0, 0, 0);
        cairo_move_to(cr,add_a+add_c/2-20,add_b+add_d/2);
        cairo_show_text(cr,"ADD NODE");

       while(!level_order.empty())
        {
                //cairo_set_source_rgb(cr, 238, 180,34);
                node=level_order.front();
                level_order.pop();
                if(node->y==0) node->y++;
                //cairo_set_source_rgb(cr, 238, 180,34);
                cairo_rectangle(cr, y0*(node->y)+20, x0*(node->distance)+20, y0-10,x0-80);
                //cairo_fill(cr);
                node->a=y0*(node->y)+20;
                node->b=x0*(node->distance)+20;
                node->c=y0-30;
                node->d=x0-80;
                cairo_move_to(cr,  y0*(node->y)+10+(y0-10)/2,x0*(node->distance)+20+(x0-80)/2);
                char temp_c[20];
                cairo_show_text(cr,node->name);
                if(node->parent!=NULL)
                {
                    cairo_move_to(cr,y0*(node->y)+20+(y0-10)/2,x0*(node->distance)+20);
                    cairo_line_to(cr,y0*(node->parent->y)+20+(y0-10)/2,x0*(node->parent->distance)+20+(x0-80));

                }

                attr=node->attributes;

                while(attr!=NULL)
                {
                    attr=attr->next;
                }

                if(node==NULL || node->elements==NULL) continue;
                node=node->elements;
                while(node!=NULL)
                {
                    level_order.push(node);
                    node=node->next;
                }


        }


  glob.count = 0;
  cairo_stroke(cr);

}


bool test_if_inside(int x,int y,int a,int b,int c,int d)
{
    if(x>a && y>b && x<a+c && y<b+d)
        return true;
    return false;
}

struct XMLElement *find_node(double x,double y)
{
    struct XMLElement *node,*trvel, *root;
    int check=0;
        root=Doc->elements;
        queue<struct XMLElement*> level_order;
        struct XMLAttribute *attr=NULL;
        level_order.push(root);
    while(!level_order.empty())
        {
                node=level_order.front();
                level_order.pop();
                if(test_if_inside(x,y,node->a,node->b,node->c,node->d))
                {
                    check=1;
                    break;
                }
                if(node==NULL || node->elements==NULL) continue;
                node=node->elements;
                while(node!=NULL)
                {
                    level_order.push(node);
                    node=node->next;
                }


        }
        if(check==1)
        return node;
        else
        return NULL;


};


void on_button_clicked (GtkWidget *button, GtkTextBuffer *buffer)
{

    size_t length;
    GtkTextIter start, end;
    string text;

    gtk_text_buffer_get_selection_bounds (buffer, &start, &end);
    text = gtk_text_buffer_get_text (buffer, &start, &end, FALSE);

    unsigned int n = text.find("Name:");
    unsigned int a = text.find("Attributes:");
    unsigned int v = text.find("Value:");
    int i,j;
    std::string name;

    //cout <<"---------------"<<'\n';
    for(i=(n+5);i<(a-1);i++)
    name=name+text[i];
    for(j=(a+11);j<(v-2);j++)
    attribute=attribute+text[j];


    std::string value = text.substr ((v+6));
    n1=new char[name.length() + 1];
    v1=new char[value.length() + 1];
    a1=new char[attribute.length()];
    std::strcpy(v1,value.c_str());

    std::strcpy(n1,name.c_str());

    std::strcpy(a1,attribute.c_str());

    //cout <<"..."<< n1  <<v1 <<"::::";
}


static gboolean clicked(GtkWidget *widget, GdkEventButton *event, gpointer user_data)
{

    if (add_flag==0 && (event->button == 1) && cut_flag==0 && cut==NULL && !test_if_inside(event->x,event->y,add_a,add_b,add_c,add_d) )
        {

            cut_x=event->x;
            cut_y=event->y;
            //cout<<cut_flag<<"Hoo la"<<endl;
            cut=find_node(cut_x,cut_y);
            if (cut==NULL)
                return 0;
            //if(cut!=NULL)
            //cout<<"...ABCD...";
            {
            cut_flag=1;
            //cout<<"entered  :"<<cut_flag<<endl;
            struct XMLElement *temp=cut->parent;
            //cout<<cut->parent->name<<endl;
            temp=temp->elements;
            if(temp==cut)
            {
                cut->parent->elements=cut->next;
                cut->next=NULL;

            }

            else
            {

                while((temp->next)!=cut && (temp->next)!=NULL)
                temp=temp->next;
                temp->next=temp->next->next;
                temp->next->parent=NULL;

            }

            }
            return true;
        }
    else if (add_flag==0 && event->button == 1 && cut_flag==1 && cut!=NULL && !test_if_inside(event->x,event->y,add_a,add_b,add_c,add_d))
        {

            cut_x=event->x;
            cut_y=event->y;
            //cout<<"heyyy"<<endl;
            cutf=find_node(cut_x,cut_y);
            if(cutf==cut)
                return 0;

            if(cutf!=NULL)
            {


            cut->next=cutf->elements;
            cutf->elements=cut;
            cut->parent=cutf;
            //cout<<cutf->name<<" "<<cutf->elements->name<<endl;
            }
            out.open("note.xml");
            out<<"<?xml version=\"1.0\"?>"<<endl;
            write_file(Doc->elements->elements,NULL);
            out.close();
            gtk_widget_queue_draw(widget);
            //traverse(Doc->elements);

            cut_flag=0;
            cut=NULL;
            cutf=NULL;
            return true;
        }

 else if(event->button==1 && test_if_inside(event->x,event->y,add_a,add_b,add_c,add_d) && add_flag==0)
    {  //cout << "hshs";
        add_flag=1;
        return true;
    }

    else if(event->button==1 && add_flag==1)
    {
        GtkWidget *window, *scrolled_win, *textview,*vbox,*button;
        GtkTextBuffer *buffer;
//gtk_init (&argc, &argv);
        window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
        gtk_window_set_title (GTK_WINDOW (window), "Text Views");
        g_signal_connect (G_OBJECT (window), "destroy",G_CALLBACK (on_window_destroy),NULL);
        vbox = gtk_vbox_new (FALSE, 2);
        gtk_container_add (GTK_CONTAINER (window), vbox);

        gtk_container_set_border_width (GTK_CONTAINER (window), 10);
        gtk_widget_set_size_request (window, 250, 150);
        textview = gtk_text_view_new ();
        gtk_box_pack_start (GTK_BOX (vbox), textview, 1, 1, 0);

        buffer = gtk_text_view_get_buffer (GTK_TEXT_VIEW (textview));

        GtkTextIter iter;
        GtkTextIter end;
        GtkTextMark *cursor;

        gchar *a="Name:";


        gchar *c="\n";

        gtk_text_buffer_set_text (buffer,a , -1);

        cursor = gtk_text_buffer_get_mark (buffer, "insert");
        gtk_text_buffer_get_iter_at_mark (buffer, &iter, cursor);
        gtk_text_iter_forward_to_line_end (&iter);

        gtk_text_buffer_insert (buffer, &iter, c, -1);

        gchar *d="Attributes:";
        gchar *e,*n;
        gchar *h="=\"";
        gchar *m="\" ";
        gtk_text_buffer_insert (buffer, &iter, d, -1);
        gtk_text_buffer_insert (buffer, &iter,"\n",-1);

        gchar *f="Value:";

        gtk_text_buffer_insert (buffer, &iter, f, -1);
        scrolled_win = gtk_scrolled_window_new (NULL, NULL);
        button = gtk_button_new_with_label ("SAVE");
        gtk_box_pack_start (GTK_BOX (vbox), button, 0, 0, 0);
        g_signal_connect (G_OBJECT (button), "clicked",    G_CALLBACK (on_button_clicked),
                        buffer);


        gtk_container_add (GTK_CONTAINER (scrolled_win), textview);
        gtk_container_add (GTK_CONTAINER (window), scrolled_win);
        gtk_widget_show_all (window);
        //gtk_widget_queue_draw(widget);
        gtk_main();



        char *add_name=n1;
        char *add_value=v1;
        //char *add_attributes=a1;

        struct XMLElement *new_node=NULL;
        struct XMLElement *temp_var1=NULL;

        new_node=(struct XMLElement*)calloc(1,sizeof(struct XMLElement));
        new_node->name=add_name;
        new_node->value=add_value;

        int width=0,temp_width=0;
        struct XMLElement *node,*trvel;
        queue<struct XMLElement*> level_order;
        struct XMLAttribute *attri=NULL;
        struct XMLElement *nouse=NULL;
        int dist=0,list_len=0;
        int curr_dist=0;
        struct XMLElement* p_check=NULL;
        p_check=Doc->elements->parent;
        level_order.push(Doc->elements);
        while(!level_order.empty())
        {

                node=level_order.front();
                level_order.pop();
                if(test_if_inside(event->x,event->y,node->a,node->b,node->c,node->d))
                {
                    temp_var1=node;
                    break;
                }
                attri=node->attributes;
                while(attri!=NULL)
                {
                    //cout<<attr->name<<":"<<attr->value<<",";
                    attri=attri->next;
                }

                if(node==NULL || node->elements==NULL) continue;
                node=node->elements;
                list_len=0;

                while(node!=NULL)
                {
                    level_order.push(node);
                    node=node->next;
                }

        }

          string a11=attribute;
//cin >'[[[> a11;
//cout <<"{{{" << a11;
   //size_t  STRING_LENGTH = 256;

        char chara;int l=a11.length();
        //cout <<l<<endl;
        int i=0; int k=0;
        temp_var1->attributes=NULL;
        while(i<l)
        {

                string name="";
                string value="";
                unsigned int a = a11.find("=",(k));
                //cout << a <<endl;
                int i,j;
                for(i=k;i<(a);i++)
                name=name+a11[i];
                unsigned int a2 = a11.find("\"",(a+2));
                //cout <<a2 <<endl;
                for(i=(a+2);i<(a2);i++)
                  value=value+a11[i];

                char *an=new char[name.length() + 1];
                char *av=new char[value.length() + 1];
                i=i+(a2);
                strcpy(av,value.c_str());
                std::strcpy(an,name.c_str());
                //cout << endl <<       an << "       " <<av  << endl;


//__________attribute _________________________an=attribute name  av=attribute value
new_node->attributes=(struct XMLAttribute *)calloc(1,sizeof(struct XMLAttribute));
//cout <<"LDL";
//if(temp_var1->attributes!=NULL)
{

new_node->attributes->name=(char *)calloc(name.length()+2,sizeof(char));
strcpy(new_node->attributes->name,an);
//cout <<"LDL";
new_node->attributes->value=(char *)calloc(value.length()+2,sizeof(char));
strcpy(new_node->attributes->value,av);

//attribute_temp=attribute_temp->next;
new_node->attributes->next=temp_var1->attributes;
temp_var1->attributes=new_node->attributes;
}
             //   cout<<av << ":::::" << an;
               // cin.get();

                //cout <<k <<endl;
k=a11.find(",",(a2));
                if (k<l && k>0);
                    //cout <<k <<endl;
                else {
                        break;
                        new_node->attributes=NULL;
                    }

                k=k+1;
                //cin.get();
}


        new_node->next=temp_var1->elements;
        temp_var1->elements=new_node;
        out.open("note.xml");
        out<<"<?xml version=\"1.0\"?>"<<endl;
        write_file(Doc->elements->elements,NULL);
        //cout<<"    -------------    ";
        out.close();
        gtk_widget_queue_draw(widget);


        add_flag=0;
    }


    if (event->button == 3 && cut_flag==0) {
        {
            //return TRUE;//cout <<"SSS";
            GtkWidget *window, *scrolled_win, *textview,*vbox,*button;
            GtkTextBuffer *buffer;
            //gtk_init (&argc, &argv);
            window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
            gtk_window_set_title (GTK_WINDOW (window), "Text Views");
            g_signal_connect (G_OBJECT (window), "destroy",G_CALLBACK (on_window_destroy),NULL);
            vbox = gtk_vbox_new (FALSE, 2);
            gtk_container_add (GTK_CONTAINER (window), vbox);

            gtk_container_set_border_width (GTK_CONTAINER (window), 10);
            gtk_widget_set_size_request (window, 250, 150);
            textview = gtk_text_view_new ();
            gtk_box_pack_start (GTK_BOX (vbox), textview, 1, 1, 0);
////cout << "kkkk";
            buffer = gtk_text_view_get_buffer (GTK_TEXT_VIEW (textview));
//gchar *a="SSS";
            GtkTextIter iter;
            GtkTextIter end;
            GtkTextMark *cursor;
            struct XMLElement *temp_var1=NULL;
            temp_var1=find_node(event->x,event->y);
            attribute="";
            std::cout <<"aaa";
            gchar *a="Name:";

            gchar *b=temp_var1->name;
            gchar *c="\n";

            gtk_text_buffer_set_text (buffer,a , -1);
//cout<<"jjj";
            cursor = gtk_text_buffer_get_mark (buffer, "insert");
            gtk_text_buffer_get_iter_at_mark (buffer, &iter, cursor);
            gtk_text_iter_forward_to_line_end (&iter);
  //cout <<"hjh";
  //cin.get();

    gtk_text_buffer_insert (buffer, &iter, b, -1);
    gtk_text_buffer_insert (buffer, &iter, c, -1);
    struct XMLAttribute *attr=temp_var1->attributes;
    gchar *d="Attributes:";
    gchar *e,*n;
    gchar *h="=\"";
    gchar *m="\",";
    gtk_text_buffer_insert (buffer, &iter, d, -1);
    while(attr!=NULL)
    {  e=attr->value;
    n=attr->name;
    gtk_text_buffer_insert (buffer, &iter, n, -1);
    gtk_text_buffer_insert (buffer, &iter, h, -1);
        gtk_text_buffer_insert (buffer, &iter, e, -1);

    gtk_text_buffer_insert (buffer, &iter, m, -1);


   attr= attr->next;

    }
    gtk_text_buffer_insert (buffer, &iter,"\n",-1);

    gchar *f="Value:";
    gchar *j=temp_var1->value;
    gtk_text_buffer_insert (buffer, &iter, f, -1);
    gtk_text_buffer_insert (buffer, &iter, j, -1);
//gtk_text_buffer_set_text (buffer, "Name"+a+":View: widget!\nggjgjj\nValue:gjhgjg", -1);
scrolled_win = gtk_scrolled_window_new (NULL, NULL);
  button = gtk_button_new_with_label ("SAVE");
  gtk_box_pack_start (GTK_BOX (vbox), button, 0, 0, 0);
  g_signal_connect (G_OBJECT (button), "clicked",    G_CALLBACK (on_button_clicked),
                    buffer);


gtk_container_add (GTK_CONTAINER (scrolled_win), textview);
gtk_container_add (GTK_CONTAINER (window), scrolled_win);
gtk_widget_show_all (window);
//gtk_widget_queue_draw(widget);
gtk_main();

int width=0,temp_width=0;
        struct XMLElement *node,*trvel;
        queue<struct XMLElement*> level_order;
        struct XMLAttribute *attri=NULL;
        struct XMLElement *nouse=NULL;
        int dist=0,list_len=0;
        int curr_dist=0;
        struct XMLElement* p_check=NULL;
        p_check=Doc->elements->parent;
        level_order.push(Doc->elements);
        while(!level_order.empty())
        {

                node=level_order.front();
                level_order.pop();
                if(test_if_inside(event->x,event->y,node->a,node->b,node->c,node->d))
                {
                    temp_var1=node;
                    break;
                }
                attri=node->attributes;
                while(attri!=NULL)
                {
                    //cout<<attr->name<<":"<<attr->value<<",";
                    attri=attri->next;
                }

                if(node==NULL || node->elements==NULL) continue;
                node=node->elements;
                list_len=0;

                while(node!=NULL)
                {
                    level_order.push(node);
                    node=node->next;
                }

        }

    string a11=attribute;
//cin >'[[[> a11;
//cout <<"{{{" << a11;
   //size_t  STRING_LENGTH = 256;

        char chara;int l=a11.length();
        //cout <<l<<endl;
        int i=0; int k=0;
        temp_var1->attributes=NULL;
        while(i<l)
        {

                string name="";
                string value="";
                unsigned int a = a11.find("=",(k));
                //cout << a <<endl;
                int i,j;
                for(i=k;i<(a);i++)
                name=name+a11[i];
                unsigned int a2 = a11.find("\"",(a+2));
                        //cout <<a2 <<endl;
                        for(i=(a+2);i<(a2);i++)
                        value=value+a11[i];


                  char *an=new char[name.length() + 1];
                  char *av=new char[value.length() + 1];
                i=i+(a2);
                strcpy(av,value.c_str());
                std::strcpy(an,name.c_str());
//cout << endl <<       an << "       " <<av  << endl;

//__________attribute _________________________an=attribute name  av=attribute value
struct XMLAttribute *attribute_temp=(struct XMLAttribute *)calloc(1,sizeof(struct XMLAttribute));
//cout <<"LDL";
//if(temp_var1->attributes!=NULL)
{

attribute_temp->name=(char *)calloc(name.length()+2,sizeof(char));
strcpy(attribute_temp->name,an);
//cout <<"LDL";
attribute_temp->value=(char *)calloc(value.length()+2,sizeof(char));
strcpy(attribute_temp->value,av);

//attribute_temp=attribute_temp->next;
attribute_temp->next=temp_var1->attributes;
temp_var1->attributes=attribute_temp;
}
             //   cout<<av << ":::::" << an;
               // cin.get();

                //cout <<k <<endl;
k=a11.find(",",(a2));
                if (k<l && k>0);
                    //cout <<k <<endl;
                else {
                        break;
                        attribute_temp=NULL;
                    }

                k=k+1;
                //cin.get();
}

//cin.get();



//cout <<"hggd";
//cout<<endl<<endl<<n1<<"                    "<<v1<<endl<<endl<<endl;
//cout <<"fff" << n1;

strcpy(temp_var1->name,n1);
strcpy(temp_var1->value,v1);
//cout<<"sdsds" << "......." <<temp_var1->value;
//cout<<"sdsds" << "......." <<temp_var1->name;


traverse(Doc->elements);
//std::strcpy(temp_var1->name,n1);
//std::strcpy(temp_var1->value,v1);
out.open("note.xml");
out<<"<?xml version=\"1.0\"?>"<<endl;
write_file(Doc->elements->elements,NULL);
//cout<<"    -------------    ";

out.close();
gtk_widget_queue_draw(widget);

        }


gtk_widget_queue_draw(widget);
    }


    return TRUE;
}
//}
int main(int argc, char *argv[])
{


  GtkWidget *window;
  GtkWidget *darea;
  GtkWidget *grid;
  GtkWidget *swindow;
  GtkWidget *viewport;
  glob.count = 0;

  gtk_init(&argc, &argv);

  window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  grid = gtk_grid_new();
  swindow = gtk_scrolled_window_new (NULL,NULL);
  viewport = gtk_viewport_new (NULL,NULL);
  darea = gtk_drawing_area_new();
  //gtk_container_add(GTK_CONTAINER(window), darea);
   gtk_widget_set_size_request (window, 500, 600);
  gtk_widget_set_size_request (darea, 9000, 600);

  gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (swindow),GTK_POLICY_ALWAYS,GTK_POLICY_NEVER);

  gtk_widget_set_hexpand(GTK_WIDGET(swindow), TRUE);
  gtk_widget_set_vexpand(GTK_WIDGET(swindow), TRUE);

  gtk_container_add (GTK_CONTAINER(viewport), darea);
  gtk_container_add (GTK_CONTAINER(swindow), viewport);
  gtk_grid_attach (GTK_GRID(grid), swindow, 0, 0, 1, 1);
  gtk_container_add (GTK_CONTAINER(window), grid);

  gtk_widget_add_events(window, GDK_BUTTON_PRESS_MASK);

  g_signal_connect(G_OBJECT(darea), "draw",G_CALLBACK(on_draw_event), NULL);
  g_signal_connect(window, "destroy",G_CALLBACK(gtk_main_quit), NULL);
  g_signal_connect(window, "button-press-event",G_CALLBACK(clicked), NULL);

  gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
  gtk_window_set_default_size(GTK_WINDOW(window), 800, 600);
  gtk_window_set_title(GTK_WINDOW(window), "Lines");

  gtk_widget_show_all(window);
  if(marker==1)
  {
      marker=0;
      return 0;
  }

  gtk_main();
char p_name[10];
cout<<"Enter node name"<<endl;
cin>>p_name;
struct XMLElement *ret_val;
cout<<p_name;
cout<<endl<<"searching"<<endl;
ret_val=getChildElement(p_name);
getNodeContent(ret_val->parent);
cout<<"enter attribute name"<<endl;
cin>>p_name;
cout<<getValueAttr(p_name,ret_val->parent);


  return 0;
}

