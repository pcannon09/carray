#include <stdlib.h>

#include "carray/carr.h"
#include "carray/CARRpredefines.h"

CARR carr_init(const size_t cap, const bool dynamic)
{
	CARR vec = {
		.cap = cap,
		.size = 0,
		.dynamic = dynamic,
		.__initialized = false,
		.vec = NULL
	};

	vec.vec = calloc(cap, sizeof(*vec.vec));

	if (!vec.vec)
		return vec;

	vec.__initialized = true;

	return vec;
}

CARRError carr_resize(CARR *vec, const size_t newCap)
{
	if (!vec || !vec->__initialized)
		return CARR_VEC_NULL;

	if (newCap <= vec->cap)
		return CARR_VEC_ResizeError;

	void **tmpVec = realloc(
		vec->vec,
		newCap * sizeof(*vec->vec));

	if (!tmpVec)
		return CARR_VEC_OOM;

	vec->vec = tmpVec;
	vec->cap = newCap;

	return CARR_VEC_OK;
}

CARRError carr_replaceIndex(CARR *vec, void *item, const size_t idx)
{
	if (!vec || !vec->__initialized)
		return CARR_VEC_NULL;

	if (idx >= vec->cap)
		return CARR_VEC_OutOfBounds;

	vec->vec[idx] = item;

	return CARR_VEC_OK;
}

CARRError carr_pushFront(CARR *vec, void *item)
{
	if (!vec || !vec->__initialized)
		return CARR_VEC_NULL;

	if (vec->size >= vec->cap)
	{
		if (!vec->dynamic)
			return CARR_VEC_OutOfBounds;

		const CARRError error =
			carr_resize(
				vec,
				vec->cap + CARR_VECTOR_CAP_ADDITION);

		if (error != CARR_VEC_OK)
			return error;
	}

	for (size_t i = vec->size ; i > 0 ; --i)
		vec->vec[i] = vec->vec[i - 1];

	vec->vec[0] = item;
	vec->size++;

	return CARR_VEC_OK;
}

CARRError carr_deleteIndex(CARR *vec, const size_t index, const bool fall)
{
	if (!vec || !vec->__initialized)
		return CARR_VEC_NULL;

	if (!fall)
	{
		vec->vec[index] = NULL;

		return CARR_VEC_OK;
	}

	// else:
	// NOT (expr) !!
	if (!(vec->size > index + 1))
		return CARR_VEC_OutOfBounds;

	// Shift element by ONE
	for (size_t i = index ; i + 1 < vec->size ; ++i)
		vec->vec[i] = vec->vec[i + 1];

	vec->vec[vec->size - 1] = NULL;
	vec->size--;

	return CARR_VEC_OK;
}

CARRError carr_pushBack(CARR *vec, void *item)
{
	if (!vec || !vec->__initialized)
		return CARR_VEC_NULL;

	if (vec->size >= vec->cap && vec->dynamic)
	{
		const CARRError error =
			carr_resize(vec, vec->cap + CARR_VECTOR_CAP_ADDITION);

		if (error != CARR_VEC_OK)
			return error;
	}

	const CARRError error = 
		carr_replaceIndex(vec, item, vec->size);

	if (error != CARR_VEC_OK)
		return error;

	vec->size++;

	return CARR_VEC_OK;
}

CARRError carr_reverse(CARR *vec)
{
	if (!vec || !vec->__initialized)
		return CARR_VEC_NULL;

	for (size_t i = 0 ; i < vec->size / 2 ; ++i)
	{
		void *tmp = vec->vec[i];

		vec->vec[i] = vec->vec[vec->size - 1 - i];
		vec->vec[vec->size - 1 - i] = tmp;
	}

	return CARR_VEC_OK;
}

void carr_destroy(CARR *vec)
{
	CARR_FREE(vec->vec);

	vec->__initialized = false;
	vec->cap = 0;
	vec->size = 0;
}

