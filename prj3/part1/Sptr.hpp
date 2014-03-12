#include <assert.h>
#include <iostream>
//#include <pthread.h>

using namespace std;
namespace cs540{
/*
pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutex2 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutex3 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutex4 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutex5 = PTHREAD_MUTEX_INITIALIZER;

*/
class RefCount_base
{
	public:
	virtual void addRef() = 0;
	virtual int cutRef() = 0;
	virtual ~RefCount_base() {}
	virtual void* pptr() = 0;
	
};

/* RC class*/
template<typename Type>
class RefCount : public RefCount_base
{
	private:
		int count;
		Type *pointee;
		void release()
		{
			if(pointee != 0)
			{
				delete pointee;
				pointee = 0;
//				cout<<"pontiee deleted and zerod"<<endl;
			}
		}

	public:

		RefCount(Type *p):count(1), pointee(p)
		{
			int m;
			m = pthread_mutex_init(&mutex, 0);
			assert(m == 0);
		} //
		
		virtual void *pptr(){ return pointee; } //
		virtual void addRef()
		{	
				pthread_mutex_lock(&mutex);
			count++;
				pthread_mutex_unlock(&mutex);
		} //

		virtual int  cutRef()  //
		{
			int temp;
				pthread_mutex_lock(&mutex);
			assert(count > 0);
			count--;
			temp = count;
			assert(count >=0);
				pthread_mutex_unlock(&mutex);
			return temp;
		}

		virtual ~RefCount() //
		{
//			cout<<"in refCount dest :: before release "<<endl;
			release(); 
//			cout<<"in refCount dest :: after release "<<endl;
		}

		pthread_mutex_t mutex;
};
////////////////////////////////

class safe_bool
{
protected:
   void safe_bool_true() const {}
 
   typedef safe_bool this_type;  
   typedef void (this_type::*unspecified_bool_type)() const;
};

////////////////////////////////
/* sptr class*/
template <typename T> 
class Sptr : public safe_bool{

	//friends
		template <typename T1, typename U1> friend
		Sptr<T1> dynamic_pointer_cast(const Sptr<U1> &sp);

		template <typename T1, typename T2> friend
		bool operator==(const Sptr<T1> &sp1, const Sptr<T2> &sp2);

		template <typename T1, typename U1> friend
		Sptr<T1> static_pointer_cast(const Sptr<U1> &sp);

	/////		
	public:
		RefCount_base *rc;

/* member functions */

		//typedef void (Sptr::*unspecified_bool_type);
		operator unspecified_bool_type() const
    {
			//ok_ = true;
			return rc==0 ? 0 : &this_type::safe_bool_true ;//ok_ ? &this_type::safe_bool_true : 0;
    }
///////////////////////////////////////////////look up
		Sptr(): rc(0){}

		Sptr(T *pval)
		{
			if(pval == 0)
				rc =0;
			else
				rc = new RefCount<T>(pval);
		}

		Sptr(const Sptr &sp)//: ptr(sp.ptr),  rc(sp.rc)
		{
 //pthread_mutex_lock(&mutex1);
			rc = sp.rc;//getCount();
			if(rc !=0 )
				rc->addRef();
 //pthread_mutex_unlock(&mutex1);
		}

		~Sptr()		//dest
		{
			decrement();
		}

	  template<typename U>
		Sptr(U *usp)			//const. a smart ptr
		{
 //pthread_mutex_lock(&mutex4);
			rc = new RefCount<U>(usp);
 //pthread_mutex_unlock(&mutex4);
		}

		template<typename U>
		Sptr(const Sptr<U> &usp)
		{
 //pthread_mutex_lock(&mutex5);
			rc = usp.rc;//getCount();
			if(rc != 0)
      	rc->addRef();
	//pthread_mutex_unlock(&mutex5);
		}

		template<typename U>
		Sptr<T> &operator=(const Sptr<U> &usp) //; 
		{
//pthread_mutex_lock(&mutex7);
			if(usp.rc != 0)
				usp.rc->addRef();

			decrement();

			rc = usp.rc;//.getCount();
//pthread_mutex_unlock(&mutex7);
			return *this;
		}
//
  	Sptr &operator=(const Sptr &sp) 
    {
			if(sp.rc != 0)
				sp.rc->addRef();

			if(rc != 0)
				decrement();

			rc = sp.rc;
//pthread_mutex_unlock(&mutex8);
      return *this;
    }


		void reset()
		{
//			cout<<"reset decrement "<<endl;
			decrement();
			//cout<<" ********************* After resttt "<<endl;
//pthread_mutex_lock(&mutex10);
			this->rc = 0;			/////////th///////////////////////////////
//pthread_mutex_unlock(&mutex10);
			//cout<<" ********************* After resttt rc = 0"<<endl;
		}

		T &operator*() const//; // *
		{
			assert(rc != 0);
			//T *temp =  reinterpret_cast<T*>(rc->pptr());
			return *(reinterpret_cast<T*>(rc->pptr()));// *temp;
		}

		T *operator->() const //; // ->
		{
			assert(rc != 0);
			 return reinterpret_cast<T*>(rc->pptr());
			//	return rc->pptr();
		}

		T *get() const
		{
				assert(rc != 0);
				return  reinterpret_cast<T*>(rc->pptr());
		}

		RefCount_base *getCount() const
		{
				return rc;
		}


	private:
		void decrement()
		{
//pthread_mutex_lock(&mutex11);
			if(rc != 0)
			{
				int temp = rc->cutRef();
				//cout << "*************************** refCount"<<temp<<endl;
				if(temp == 0)
				{
					//cout<<"DELETE RC"<<endl;
					delete rc;
					rc = 0;
				}
			}
//pthread_mutex_unlock(&mutex11);
		}
};


/* free functions */
template <typename T1, typename T2>
bool operator==(const Sptr<T1> &sp1, const Sptr<T2> &sp2)
{
	if((sp1.getCount() !=0 ) && sp2.getCount() != 0)
	return (sp1.getCount()->pptr() == sp2.getCount()->pptr());
	else
		return false;
}


//look hereeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeee
template <typename T, typename U>
Sptr<T> static_pointer_cast(const Sptr<U> &sp)
{
	//check if it is castable
	T *temp =  static_cast<T*>(sp.getCount()->pptr());
	//sp.rc->addRef();
	return (Sptr<T>)sp;
}



template <typename T, typename U>
Sptr<T> dynamic_pointer_cast(const Sptr<U> &sp)
{
	RefCount<T> *rptr = dynamic_cast<RefCount<T> *>(sp.getCount());

	if(rptr == 0)
	{
		return Sptr<T>();
	}
	return (Sptr<T> )sp;
}





/*  impl. */


}
