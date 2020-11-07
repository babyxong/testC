struct test_struct {
           int num;
          char ch;
          float f1;
  };
 int main(void)
  {
          struct test_struct *test_struct;
          struct test_struct init_struct ={12,'a',12.3};
          
          
          char *ptr_ch = &init_struct.ch;
          
          
          test_struct = container_of(ptr_ch,struct test_struct,ch);
          
          
          printf("test_struct->num =%d\n",test_struct->num);
          printf("test_struct->ch =%c\n",test_struct->ch);
          printf("test_struct->ch =%f\n",test_struct->f1);
          return 0;
  }