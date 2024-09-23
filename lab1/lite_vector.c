#include "lite_vector.h"
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

lite_vector* lv_new_vec(size_t type_size) {
  lite_vector * vec = malloc(sizeof(lite_vector)); // create the lite_vector
  if(vec == NULL) { // stop and return if allocation has failed
    return NULL;
  }
  vec->type_size = type_size; // save this value even though it is useless
  vec->max_capacity = 1000; // have an initial max capacity of 1000 elements
  vec->length = 0; // set starting length to 0
  
  vec->data = malloc(sizeof(void *) * vec->max_capacity); // allocate space for data array
  if(vec->data == NULL) { // free the vector if memory allocation has failed
    free(vec);
    return NULL;
  }
  return vec; // return the vector if everything was successful
}

void lv_cleanup(lite_vector* vec) {
  if(vec == NULL) { // check to make sure the vector is not null
    return;
  }
  for(int i=0; i<vec->length; i++) { // free data allocated when doing the memcpy in lv_append
    free(vec->data[i]);
  }
  free(vec->data); /// free the data array
  free(vec); // free the vector
}

bool lv_clear(lite_vector* vec) {
  if(vec == NULL) { // make sure the vector is not null before trying to clear it
    return false;
  }
  for(int i=0; i<vec->length; i++) { // free data allocated when doing the memcpy in lv_append
    free(vec->data[i]);
  }
  vec->length = 0; // reset the length to 0 since the contents of the vector have been cleared (freed)
  return true;
}

size_t lv_get_length(lite_vector* vec) {
  if(vec == NULL) { // make sure the vector is not null before trying to access its length
    return 0;
  }
  return vec->length; // return the current length of the vector
}

void* lv_get(lite_vector* vec, size_t index) {
  if(vec == NULL) { // make sure the vector is not null before trying to access an element
    return NULL;
  }
  else if(index > vec->length - 1) { // make sure the index is valid 
    return NULL;
  }
  return vec->data[index]; // return the element from the given index
}

/**
 * lv_resize is essentially private since we marked it static.
 * The job of this function is to attempt to resize the vector.
 * There may be functions you can call to do this for you, or
 * you may write it yourself.  Either way it isn't too hard.
 * With everything though, check to make sure the code worked
 * and return appropriately.  Do NOT destroy the data if the code
 * fails.  If the resize cannot complete, the original vector
 * must remain unaffected.
 */
static bool lv_resize(lite_vector* vec) {
  if(vec == NULL) { // make sure the vector is not null before trying to resize
    return false;
  }
  // attempt to resize the vector
  void* resized_vec = realloc(vec->data, sizeof(void *) * (vec->max_capacity + 1000));
  if(resized_vec == NULL) { // check if the resize was successful 
    return false;
  }
  vec->data = resized_vec; // set data to the newly allocated memory (could be same if not moved)
  vec->max_capacity += 1000; // increment the max_capacity accordingly
  return true;
}

bool lv_append(lite_vector* vec, void* element) {
  if(vec == NULL) { // make sure the vector is not null before trying to append to it
    return false;
  }
  if(vec->length == vec->max_capacity) { // check if a resize is needed
    bool resize_status = lv_resize(vec);
    if(resize_status == false) { // return false if the resize failed
      return false;
    }
  }
  // vec->data[vec->length++] = element; // orginal solution not using memcpy

  vec->data[vec->length] = malloc(sizeof(void *)); // allocate space at the proper location
  if(vec->data[vec->length] == NULL) { //ensure that the allocation was succesful before memcpy
    return false;
  }
  memcpy(vec->data[vec->length++], element, sizeof(void *)); //memcpy (extra credit) and increment length
  return true;
}
