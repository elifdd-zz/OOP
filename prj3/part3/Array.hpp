#include <iostream>
#include <assert.h>
#include <string>

using namespace std;
namespace cs540
{
	/*exception*/
	class OutOfRange {
	public:
    OutOfRange():message("OUT OF RANGE EXCEPTION BY ELIF"){} 
		const char * what() const {return message;}
	private:
		const char *message;
	};//end exception

	template <unsigned int D, typename T>
	class Array; //decl



	//subarray
	template <unsigned int D, typename T>
	class SubArray
	{
		const size_t * const subarray_dims;
		const size_t * const subarray_len;
		T * const subarray_elems; // The elements

		SubArray<D, T>(T * elems, const size_t * dimens, const size_t * p_subarray_len)
		:subarray_elems(elems),subarray_dims(dimens),subarray_len(p_subarray_len)
		{
			// cout<<"Subaary Const <D, T> !!!!!!!!!!!!1"<<endl;
		} 

		public:

   	SubArray<D-1, T> operator [](size_t index)
   	{
			// cout<<"@@@@@@6 in T & operator [] (size_t index) "<<endl;
			if(!(index <subarray_dims[0]))
				throw OutOfRange();

			return
				SubArray<D-1, T>(&subarray_elems[index*subarray_len[0]],
					subarray_dims+1,subarray_len+1);
		}

		const SubArray<D-1, T>
		operator [](size_t index) const
		{
			//cout<<"@@@@@5 in T & operator [] (size_t index) const"<<endl;	
			if(!(index<subarray_dims[0]))
				throw OutOfRange();

			return
				SubArray<D-1, T>(&subarray_elems[index*subarray_len[0]],
					subarray_dims+1,subarray_len+1);
		}

		friend class Array<D+1, T>; 
		friend class SubArray<D+1, T>; 
	};//end subarray



	///partial spec.
	template <typename T>
	class SubArray<1, T>
	{
		const size_t * const subarray_dims;
		T * const subarray_elems; // The elements
		SubArray<1, T>(T * elems, const size_t * dimens, const size_t * p_subarray_len)
						:subarray_elems(elems),subarray_dims(dimens)
		{
					//cout<<"Subarray const ############"<<endl;
		}

		public:

   	T & operator [] (size_t  index)
   	{
			//cout<<"@@@@4 in T & operator [] (size_t index)"<<endl;
			if(!(index < subarray_dims[0]))
				throw OutOfRange();
			return subarray_elems[index];
		}

		const T & operator [] (size_t index) const
		{
			//cout<<"@@@3 in T & operator [] (size_t index) const"<<endl;
			if(!(index < subarray_dims[0]))
				throw OutOfRange();
			return subarray_elems[index];
		}

		friend class Array<2, T>;//<T, 2>;
		friend class SubArray<2, T>;//<T, 2>; 
	};//and part spec



// array class
	template <unsigned int D, typename T>
	class Array
	{
		T  * array_elems; // Points to all element
		size_t  num_array_elems; // Total number of array elements

		size_t  array_dims[D]; // Sizes of the N dimensions
		size_t  array_subarray_len[D]; // Dimensions of subarrays

		public:
			Array<D, T>(): array_elems(NULL), num_array_elems(0){}
			~Array<D, T>() { delete [] array_elems; }
 
			SubArray<D-1, T> operator [] (size_t index) 
			{
				//cout<<"@@2 in  SubArray<D-1, T> operator [] (size_t index)"<<endl;
				if(!(index< array_dims[0]))
					throw OutOfRange();
  
				return SubArray<D-1, T>
								(&array_elems[index*array_subarray_len[0]],array_dims+1, array_subarray_len+1);
   		}

			
			const SubArray<D-1, T>
			operator [] (size_t index) const 
			{
				//cout<<"@1 in  SubArray<D-1, T> operator [] (size_t index) const"<<endl;
				if(!(index< array_dims[0]))
					throw OutOfRange();

				return SubArray<D-1, T>
								(&array_elems[index*array_subarray_len[0]],array_dims+1,array_subarray_len+1);
			}

		/* template <typename U>
    Array(const Array<D, U> &)
    {
       cout<<" in  Array(const Array<D, U> &) "<<endl;
    }*/

		Array(size_t (&arr)[D])
		{
			size_t big_size = 1;
      //cout<<" in  Array(size_t (&)[D]) "<<endl;
			for(size_t i = 0; i<D; i++)
				big_size *=arr[i];

				num_array_elems = big_size;

				array_elems = new T[big_size];
      	//cout<<"ARRAY SIZE :"<<big_size<<endl;

				copy(&arr[0],&arr[D-1], array_dims);		/////////////////////////////////////////////////////
				array_dims[D-1] = arr[D-1];//m_Dimensions[D-1]=dim;

//			for(int i = 0; i<D; i++)
//				cout<<array_dims[i]<<endl;

				for(int j =0 ; j<D; j++)
					array_subarray_len[j] =1;

				for(int i =0 ; i<D; i++)
				{
					for(int j =i+1 ; j<D; j++)
					array_subarray_len[i] *= array_dims[j]; 
				}

//				 for(int j =0 ; j<D; j++)
//       		cout<<array_subarray_len[j]<<endl;
    	}

	};//end Array

}//end namespace
