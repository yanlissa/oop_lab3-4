#pragma once

template<class InputIterator, class UnaryPredicate>
InputIterator findIf (InputIterator first, InputIterator last, UnaryPredicate pred)
{
	while (first!=last) {
		if (pred(*first)) return first;
		++first;
	}
	return last;
}

template <class ForwardIterator>
ForwardIterator minElement ( ForwardIterator first, ForwardIterator last )
{
	if (first==last) return last;
	ForwardIterator smallest = first;

	while (++first!=last)
		if (*first<*smallest)
			smallest=first;
	return smallest;
}

template <class ForwardIterator>
ForwardIterator maxElement ( ForwardIterator first, ForwardIterator last )
{
	if (first==last) return last;
	ForwardIterator largest = first;

	while (++first!=last)
		if (*largest<*first)
			largest=first;
	return largest;
}

template<class InputIterator, class Function>
void forEach(InputIterator first, InputIterator last, Function fn)
{
	while (first!=last) {
		fn (*first);
		++first;
	}
}

template <class InputIterator, class OutputIterator, class UnaryPredicate>
OutputIterator copyIf (InputIterator first, InputIterator last,
		OutputIterator result, UnaryPredicate pred)
{
	while (first!=last) {
		if (pred(*first)) {
			*result = *first;
			++result;
		}
		++first;
	}
	return result;
}

template <class BidirectionalIterator>
BidirectionalIterator Partition ( BidirectionalIterator first, BidirectionalIterator last )
{
	BidirectionalIterator pivot = last;
	pivot--;
	BidirectionalIterator p_index = first;
	while (first != last) {
		if (*first < *pivot) {
			std::swap(*first, *p_index);
			p_index++;
		}
		first++;
	}
	std::swap(*pivot, *p_index);
	return p_index;
}

template <class BidirectionalIterator>
void Sort ( BidirectionalIterator first, BidirectionalIterator last )
{
	if (first==last) return;
	BidirectionalIterator pivot = Partition(first, last);
	Sort(first, pivot);
	pivot++;
	Sort(pivot, last);
}
