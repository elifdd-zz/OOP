#define  DynamicArray_DEFINE(typ)		\
typedef struct _DynamicArray_##typ{ 		\
        typ *list;\
        int size;\
        int capacity;\
	const char type[sizeof("DynamicArray_"#typ)];\
        void (*push_back)(struct _DynamicArray_##typ *, typ); \
	void (*resize)(struct _DynamicArray_##typ *, int);\
	void (*reserve)(struct _DynamicArray_##typ *, int);\
	typ& (*at)(struct _DynamicArray_##typ *, int);\
	void (*delet)(struct _DynamicArray_##typ *);\
}DynamicArray_##typ;\
/*******************************************************************************/  \
/*protos*/ \
void my_push_back(DynamicArray_##typ *, typ); \
void my_resize(struct _DynamicArray_##typ *, int);\
typ &my_at(struct _DynamicArray_##typ *, int); \
void my_reserve(struct _DynamicArray_##typ *, int); \
void my_delete(struct _DynamicArray_##typ *); \
/********************************************************************************/ \
DynamicArray_##typ *DynamicArray_##typ##_new(){\
        DynamicArray_##typ *array =(DynamicArray_##typ *)malloc(sizeof(DynamicArray_##typ));\
	array->size = 0;\
        array->capacity = 0;\
	strcpy((char*)array->type, "DynamicArray_"#typ);\ 
	array->list = (typ *)malloc(sizeof(array->list)*(array->size));\
        array->push_back = my_push_back;\
	array->resize = my_resize; \
        array->at = my_at;\
	array->reserve = my_reserve;\
	array->delet = my_delete;\
	return array;\
}\
/****************************************************************************/\
void my_delete(struct _DynamicArray_##typ *l){\
	free(l->list);\
	free(l);\
}\
/****************************************************************************/\
typ &my_at(struct _DynamicArray_##typ *l, int index){ \
	if( (index+1 >= (l->capacity)) || (index <-1)){ \
		printf("index out of range\n"); \
		exit(1); \
	}else{ \
		return (l->list[index+1]); \
	} \
} \
/****************************************************************************/\
void my_push_back(DynamicArray_##typ *l, typ m){\
        typ *tmp;\
	if(l->capacity == l->size)\
        {\
                tmp = (typ *)malloc(sizeof(tmp) * (l->size + 1) );  /*if not enough space*/ \
		if(tmp == NULL){\
		exit(1);\
		}\
		int i;\
        	for(i=0; i< (l->size) ; i++)\
                	tmp[i] = l->list[i];\
                free(l->list);\
                l->list = tmp;\
                l->capacity = (l->size) +1;\
	}\
	l->list[(l->size)] = m;\
	l->size = l->size +1;\
}\
/****************************************************************************/\
void my_reserve(struct _DynamicArray_##typ *l, int n){\
	if(n < (l->capacity)){\
		/*do nothing*/\
	}else{\
		typ *tmp;\
         	tmp = (typ *)malloc(sizeof(tmp) * n );  /*if not enough space*/\
                if(tmp == NULL){\
                        exit(1);\
               	}\
        	int i;\
                for(i=0; i< (l->size) ; i++) \
                        tmp[i] = l->list[i];\
	        l->capacity = n;\
                free(l->list);\
                l->list = tmp;\
	}\
}\
/****************************************************************************/\
void my_resize(struct _DynamicArray_##typ *l, int n){\
	if(n < (l->size)){\
 		typ *tmp;\
        	tmp = (typ *)malloc(sizeof(tmp) * (l->capacity) );  /*if not enough space*/\
        	if(tmp == NULL){\
                	exit(1);\
        	}\
		int i;\
                for(i=0; i< n ; i++)\
                       	tmp[i] = l->list[i];\
		free(l->list);\
        	l->list = tmp;\
        	l->size = n;\
	}else if(n >= (l->size)){\
		if(n > (l->capacity)){\
			typ *tmp;\
                	tmp = (typ *)malloc(sizeof(tmp) * n );  /*if not enough space*/\
                	if(tmp == NULL){\
                        	exit(1);\
                	}\
			int i;\
                	for(i=0; i< (l->size) ; i++)\
                        	tmp[i] = l->list[i];\
			l->capacity = n;\
			free(l->list);\
        		l->list = tmp;\
        		l->size = n;\
		}else{\
			int j,i;\
			j =  n - (l->size);	/*fill with this many dumb elements */\
			for(i=0;i<j;i++){\
				/*typ t = NULL;*/\
				/*l->list[ i + (l->size) ] = (typ)t; */ /* fill blanks with 0 */\
			}\
			l->size = n;\
		}\
	}\
}\
/****************************************************************************/
