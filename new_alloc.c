/* the same as malloc and ensure the allocation is effective */

void *alloc(size_t size)
{
  void *new_mem;
  new_mem = malloc(size);
  if (new_mem == NULL){
    perror("malloc: out of memory");
    exit(EXIT_FAILURE);
  }
  return new_mem;
}
