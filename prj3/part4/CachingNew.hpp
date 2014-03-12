#include <iostream>
#include <malloc.h>

using namespace std;

//namespace cs540
//{

	template <typename T> 
	class CachingNew
	{
		public:
			T *space;
			static T *space_ptr;

		CachingNew():space(0)
		{
//			cout<<"CachingNew const"<<endl;
		}
///////////
		void *operator new(size_t size)
		{
	//		cout<<"CachingNew new"<<endl;
			if(size > sizeof(T))
			{
				//cout<<"not enough space-runtime error expected"<<endl;
			}
			if(space_ptr == 0)
			{
	//			cout<<"mallocing"<<endl;
				return (T *)malloc(size);
			}else	{
				T *temp = space_ptr;
				space_ptr = space_ptr->space;
				return temp;

			}
		}
//////////////
		void operator delete(void *ptr)
		{
		//	cout<<"CachingNew delete"<<endl;
			T *temp = (T *)ptr;
			temp->space = space_ptr;
			space_ptr = temp;
		}

	};

template<typename T>
T* CachingNew<T>::space_ptr = 0;

//}
