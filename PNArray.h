#pragma once

#include <memory>

template<class _T>
class PNArray
{
public:
	using Index_t = int64_t;
	using Size_t = Index_t;

	using UniquePtr = std::unique_ptr<PNArray<_T>>;
	using Ptr = std::shared_ptr<PNArray<_T>>;
	using ConstPtr = std::shared_ptr<const PNArray<_T>>;

	PNArray();								// Default constructor
	PNArray(Index_t begin, Index_t end);	// Allocate constructor
	PNArray(Size_t size);					// Allocate constructor
	PNArray(const PNArray& obj);			// Copy constructor
	~PNArray();						// Destructor

	void Create(Index_t begin, Index_t end);
	void Create(Size_t size);
	void Create(const PNArray& obj);
	void Delete();
	void Copy(const PNArray& input);
	void CopyTo(PNArray* output) const;
	void Resize(Index_t begin, Index_t end, _T ini_all_val = 0);
	void Resize(Size_t size, _T ini_all_val = 0);
	void Fill(Index_t begin, Index_t end, _T val);
	void Fill(_T value);
	void Zeros();
	void Ones();
	Index_t Begin() const;
	Index_t End() const;
	Size_t Size() const;
	bool Empty() const;
	_T& At(Index_t id) const;
	
	_T& operator[](Index_t idx) const;
	PNArray& operator=(const PNArray& obj);
	PNArray& operator+(const PNArray& obj);
	PNArray& operator-(const PNArray& obj);
	PNArray& operator*(double f);
	friend PNArray operator*(double f, const PNArray& obj);
	PNArray operator/(double f);

private:
	_T*		_data;
	Index_t _begin, _end;

	_T* _Allocate(Index_t begin, Index_t end);
	void _Release();
	void _Fill(Index_t nl, Index_t nh, _T val);
	void _Copy(const PNArray& obj);
};

template<class _T> inline
_T* PNArray<_T>::_Allocate(Index_t begin, Index_t end)
{
	try {
		_T* buff = new _T[end - begin + 1];
	}
	catch (std::bad_alloc) {
		return nullptr;
	}
}

template<class _T> inline
void PNArray<_T>::_Release()
{
	if (!this->Empty()) {
		delete[](_data + _begin);
		_data = nullptr;
	}
}

template<class _T> inline
void PNArray<_T>::_Fill(Index_t nl, Index_t nh, _T val)
{
	if (nl < _begin || nl > _end || nh < _begin || nh > _end || _nl > _nh)
		return;
	for (Index_t i = nl; i < nh; i++)
		_data[i] = val;
}

template<class _T> inline
void PNArray<_T>::_Copy(const PNArray<_T>& obj)
{
	this->_Release();
	_begin = obj._begin;
	_end = obj._end;
	_data = this->_Allocate(_begin, _end);
	for (Index_t i = _begin; i <= _end; i++)
		_data[i] = obj._data[i];
}

///////////////////////////////////////////////////////////////////

template<class _T> inline
PNArray<_T>::PNArray()
	: _begin(0), _end(0), _data(nullptr)
{
}

template<class _T> inline
PNArray<_T>::PNArray(Index_t begin, Index_t end)
	: _begin(begin), _end(end)
{
	_data = this->_Allocate(begin, end);
}

template<class _T> inline
PNArray<_T>::PNArray(Size_t size)
	: _begin(0), _end(size - 1)
{
	_data = this->_Allocate(0, size - 1);
}

template<class _T> inline
PNArray<_T>::PNArray(const PNArray& obj)
{
	this->_Copy(obj);
}

template<class _T> inline
PNArray<_T>::~PNArray()
{
	this->_Release();
}

template<class _T> inline
void PNArray<_T>::Create(Index_t begin, Index_t end)
{
	
}
