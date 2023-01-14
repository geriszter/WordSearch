#pragma once
#define _TESTTEMP_H_

template<class T>
class Grid
{
public:
	Grid();
	~Grid();
	void SetUpGrid(const int size);

private:
	T** m_grid;
};

template<class T>
inline Grid<T>::Grid()
{
}

template<class T>
inline Grid<T>::~Grid()
{
}

template<class T>
inline void Grid<T>::SetUpGrid(const int size)
{
	m_grid = new T * [size];
	for (int i = 0; i < size; i++)
	{
		m_grid[i] = new T[size];
	}
}