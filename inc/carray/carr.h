#ifndef INCLUDE_VECTOR_VECTOR_H_
#define INCLUDE_VECTOR_VECTOR_H_

#include <stddef.h>
#include <stdbool.h>

#ifdef __cplusplus
#   define CARRVECTOR_OPEN extern "C" {
#   define CARRVECTOR_CLOSE }
#else
#   define CARRVECTOR_OPEN
#   define CARRVECTOR_CLOSE
#endif

CARRVECTOR_OPEN

/**
 * @def CARR_VECTOR_CAP_ADDITION
 * @brief Default capacity increment used by the vector implementation.
 *
 * Defines the default capacity growth increment as 16 elements.
 * The implementation may use this value when increasing capacity.
 *
 * Override this macro before including the header to customize the value.
 */
#ifndef CARR_VECTOR_CAP_ADDITION
#   define CARR_VECTOR_CAP_ADDITION 16
#endif

/**
 * @struct CARR
 * @brief Represents a pointer-based vector container.
 *
 * Stores pointers to elements in a contiguous array. Tracks the number
 * of elements currently stored and the allocated capacity.
 *
 * @warning Avoid modifying the internal fields directly
 */
typedef struct CARR
{
	/**
	 * @brief Pointer to the array of stored element pointers.
	 *
	 * Each element is a `void *`. The array itself is managed by the
	 * CARR implementation.
	 */
	void **vec;

	/**
	 * @brief Maximum number of elements that can be stored without resizing.
	 */
	size_t cap;

	/**
	 * @brief Number of elements currently stored in the vector.
	 */
	size_t size;

	/**
	 * @brief Indicates whether the vector supports dynamic resizing.
	 *
	 * When true, the vector may grow or shrink through resizing operations.
	 * When false, capacity is intended to remain fixed.
	 */
	bool dynamic;

	/**
	 * @brief Internal initialization-state flag.
	 *
	 * Used by the implementation to track whether the vector has been
	 * initialized.
	 *
	 * @internal
	 */
	bool __initialized;
} CARR;

/**
 * @enum CARRError
 * @brief Error codes returned by CARR operations.
 */
typedef enum CARRError
{
	/** @brief The operation completed successfully. */
	CARR_VEC_OK,

	/** @brief The requested index is outside the valid range. */
	CARR_VEC_OutOfBounds,

	/** @brief The requested resize operation could not be completed. */
	CARR_VEC_ResizeError,

	/** @brief Memory allocation failed. */
	CARR_VEC_OOM,

	/** @brief A required pointer argument was NULL. */
	CARR_VEC_NULL,
} CARRError;

/**
 * @brief Initializes a new CARR vector.
 *
 * Creates a vector with the requested initial capacity and resizing mode.
 *
 * @param[in] cap Initial capacity of the vector.
 * @param[in] dynamic Whether the vector supports dynamic resizing.
 *
 * @return An initialized CARR instance.
 *
 * @note Check the returned instance according to the implementation's
 *	   initialization and allocation-failure conventions.
 */
CARR carr_init(const size_t cap, const bool dynamic);

/**
 * @brief Changes the capacity of a vector.
 *
 * Requests a new capacity for the vector's underlying pointer array.
 *
 * @param[in,out] vec Pointer to the vector to resize.
 * @param[in] newCap Desired capacity.
 *
 * @return CARR_VEC_OK if successful.
 * @return CARR_VEC_NULL if a required pointer is NULL.
 * @return CARR_VEC_ResizeError if resizing fails or is not permitted.
 * @return CARR_VEC_OOM if memory allocation fails.
 *
 * @note The exact behavior when `newCap` is smaller than the current
 *	   size depends on the implementation.
 */
CARRError carr_resize(CARR *vec, const size_t newCap);

/**
 * @brief Deletes an element at a specified index.
 *
 * Removes the element at `index` from the vector.
 *
 * @param[in,out] vec Pointer to the vector to modify.
 * @param[in] index Index of the element to delete.
 * @param[in] fall Controls the deletion behavior, as defined by the
 *				 implementation.
 *
 * @return CARR_VEC_OK if successful.
 * @return CARR_VEC_OutOfBounds if `index` is invalid.
 * @return CARR_VEC_NULL if a required pointer is NULL.
 *
 * @note The meaning of `fall` and whether the removed element's pointer
 *	   is freed must be verified in the implementation.
 */
CARRError carr_deleteIndex(CARR *vec, const size_t index, const bool fall);

/**
 * @brief Replaces an element at a specified index.
 *
 * Assigns a new pointer to the element at `idx`.
 *
 * @param[in,out] vec Pointer to the vector to modify.
 * @param[in] item Pointer to the replacement element.
 * @param[in] idx Index of the element to replace.
 *
 * @return CARR_VEC_OK if successful.
 * @return CARR_VEC_OutOfBounds if `idx` is invalid.
 * @return CARR_VEC_NULL if a required pointer is NULL.
 *
 * @note This function replaces the stored pointer. Ownership and cleanup
 *	   of the previous element are determined by the implementation.
 */
CARRError carr_replaceIndex(CARR *vec, void *item, const size_t idx);

/**
 * @brief Appends an element to the end of the vector.
 *
 * Stores `item` after the current last element. Depending on the vector's
 * configuration, the operation may require additional capacity.
 *
 * @param[in,out] vec Pointer to the vector to modify.
 * @param[in] item Pointer to the element to append.
 *
 * @return CARR_VEC_OK if successful.
 * @return CARR_VEC_NULL if a required pointer is NULL.
 * @return CARR_VEC_ResizeError if the required resize cannot be performed.
 * @return CARR_VEC_OOM if memory allocation fails.
 */
CARRError carr_pushBack(CARR *vec, void *item);

/**
 * @brief Inserts an element at the beginning of the vector.
 *
 * Stores `item` at index zero and shifts existing elements as necessary.
 *
 * @param[in,out] vec Pointer to the vector to modify.
 * @param[in] item Pointer to the element to insert.
 *
 * @return CARR_VEC_OK if successful.
 * @return CARR_VEC_NULL if a required pointer is NULL.
 * @return CARR_VEC_ResizeError if the required resize cannot be performed.
 * @return CARR_VEC_OOM if memory allocation fails.
 */
CARRError carr_pushFront(CARR *vec, void *item);

/**
 * @brief Reverses the order of elements in the vector.
 *
 * Reorders the stored pointers so that the first element becomes the last,
 * the second becomes the second-to-last, and so on.
 *
 * @param[in,out] vec Pointer to the vector to reverse.
 *
 * @return CARR_VEC_OK if successful.
 * @return CARR_VEC_NULL if a required pointer is NULL.
 *
 * @note The elements themselves are not copied or modified; only their
 *	   positions in the vector are changed.
 */
CARRError carr_reverse(CARR *vec);

/**
 * @brief Destroys a vector and releases its internal resources.
 *
 * Releases resources owned by the vector implementation and invalidates
 * the vector's internal storage.
 *
 * @param[in,out] vec Pointer to the vector to destroy.
 *
 * @note This function does not return an error code.
 * @note Whether the structure is reset to a safe, reusable state depends
 *	   on the implementation.
 * @note The pointed-to elements are not assumed to be freed.
 */
void carr_destroy(CARR *vec);

CARRVECTOR_CLOSE

#endif  // INCLUDE_VECTOR_VECTOR_H_
