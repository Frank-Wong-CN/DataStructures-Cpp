#pragma once

class ElemRepresent
{
friend class Matrix;
private:
	ElemType type;
	std::any value;
	ElemRepresent *nextInRow;
	ElemRepresent *nextInColumn;
	
public:	
	ElemRepresent() : type(Real), value(0.0f), nextInRow(nullptr), nextInColumn(nullptr) {}
	
	ElemType GetType()
	{ return type; }
	
	float GetReal()
	{ return std::any_cast<float>(value); }
	
	/*
	ComplexNumber GetComp()
	{ return std::any_cast<ComplexNumber>(value); }
	*/
	
	Expression GetExpr()
	{ return std::any_cast<Expression>(value); }
	
	ElemRepresent* SetReal(float v)
	{
		type = Real;
		value = v;
		return this;
	}
	
	/*
	ElemRepresent* SetComplex(ComplexNumber v)
	{
		type = Complex;
		value = v;
		return this;
	}
	*/
	
	ElemRepresent* SetExpr(Expression v)
	{
		type = Expr;
		value = v;
		return this;
	}
};

class Matrix
{
private:
	ElemRepresent *head;
	Expression factor;
	
	size_t width;
	size_t height;
	
	bool transposed;
	
public:
	Matrix() : head(nullptr), factor(), width(0), height(0), transposed(false) {}
	Matrix(ElemRepresent *initHead, int w, int h = 1) : head(initHead), factor(), width(w), height(h), transposed(false) {}
	
	Matrix *Resize(size_t w, size_t h)
	{
		if (transposed)
		{
			size_t t = w;
			w = h;
			h = t;
		}
	
		if (!head)
			head = new ElemRepresent();
		
		for (size_t y = 0; y < h; y++)
		{
			for (size_t x = 0; x < w; x++)
			{
				if (x + y == 0)
					continue;
				
				ElemRepresent* cur = At(x + 1, y + 1);
				if (!cur)
				{
					ElemRepresent* tmp = nullptr;
					cur = new ElemRepresent();
					// Column connection
					tmp = At(x + 1, y);
					if (tmp)
						tmp->nextInColumn = cur;
					// Row connection
					tmp = At(x, y + 1);
					if (tmp)
						tmp->nextInRow = cur;
				}
			}
		}
		
		for (size_t y = height; y >= 1; y--)
		{	
			if (y == h)
				for (size_t x = width; x >= 1; x--)
					if (At(x, y)) // Should be always true
						At(x, y)->nextInColumn = nullptr;
			else if (y > h)
				for (size_t x = width; x >= 1; x--)
					if (At(x, y)) // Should be always true
						delete At(x, y);
			else
				for (size_t x = width; x >= w; x--)
					if (At(x, y))
						if (x == w)
							At(x, y)->nextInRow = nullptr;
						else
							delete At(x, y);		
		}
		
		width = w;
		height = h;
		
		return this;
	}
	
	ElemRepresent *At(size_t x, size_t y)
	{
		if (x < 1 || y < 1)
			return nullptr;
		
		if (transposed)
		{
			size_t t = x;
			x = y;
			y = t;
		}
		
		ElemRepresent *ret = head;
		for (size_t i = 0; i < x - 1; i++)
			if (ret != nullptr)
				ret = ret->nextInRow;
			else return nullptr;
		for (size_t i = 0; i < y - 1; i++)
			if (ret != nullptr)
				ret = ret->nextInColumn;
			else return nullptr;
			
		return ret;
	}
	
	Matrix *SetRange(Matrix *from, size_t x, size_t y, size_t w, size_t h)
	{
		if (!from)
			return nullptr;
		
		if (transposed)
		{
			size_t t;
			t = x;
			x = y;
			y = t;
			t = w;
			w = h;
			h = t;
		}
		
		if (x + w > width)
			Resize(x + w, height);
		
		if (y + h > height)
			Resize(width, y + h);
		
		ElemRepresent *fromElem = nullptr;
		for (int i = 0; i < w; i++)
		for (int j = 0; j < h; j++)
			if (fromElem = from->At(i, j))
			{
				switch (fromElem->GetType())
				{
				case Real:
					At(x + i, y + j)->SetReal(fromElem->GetReal());
					break;
				case Complex:
					break;
				case Expr:
					break;
				default:
					break;
				}
			}
			else
				At(x + i, y + j)->SetReal(0.0f);
			
		return this;
	}
	
	Matrix *Transpose()
	{
		transposed = !transposed;
		return this;
	}
	
	Matrix *Clear()
	{
		return Resize(0, 0);
	}
	
	const size_t &GetWidth() { if (transposed) return height; else return width; }
	const size_t &GetHeight() { if (transposed) return width; else return height; }
	
	Matrix *SubMatrix(size_t x, size_t y, size_t w, size_t h)
	{
		return new Matrix(At(x, y), w, h);
	}
	
	bool IsSquare()
	{
		return width == height;
	}
};