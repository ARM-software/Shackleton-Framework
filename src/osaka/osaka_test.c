/*
 ============================================================================
 Name        : osaka_test.c
 Author      : Andrew Sloss
 Version     : 1.0
 Copyright   : 
 
    Copyright 2019 Arm Inc., Andrew Sloss, Hannah Peeler

    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.

    Please refer to 
    https://github.com/ARM-software/Shackleton-Framework/blob/master/LICENSE.TXT
    for a full overview of the license covering this work.
    
 Description : Code for testing the validity/correctness of the Osaka Structure
 ============================================================================
 */

#include "osaka.h"
#include "osaka_test.h"

#define DEBUGIF if(mode==LOUD)

bool osaka_test_cycler(osaka_test_typ mode) {

  node_str *r0,*r1,*r2,*r3;
  node_str *c0,*c1,*c2,*c3;
  uint32_t i,x0,x1,x2,x3,t=0;
  bool test[20],b0,b1,b2,b3;

  test[t++]=true;

  
  // [00] ********************************************************

  DEBUGIF
    printf ("\n-- test 00: create 4 lists length 0,1,3 and 10 \n");


  r0= NULL;
  r1=osaka_createnode(NULL,HEAD,SIMPLE);
  r2=osaka_createnode(NULL,TAIL,SIMPLE);
  r2=osaka_createnode(r2,TAIL,SIMPLE);
  r2=osaka_createnode(r2,TAIL,SIMPLE);
  r3=NULL;

  i = 11;

  while(--i) {
    r3 = osaka_createnode(r3,TAIL,SIMPLE);
  }

  if (r0==NULL && r1!=NULL && r2!=NULL && r3!=NULL) {
    test[1] = true;
    DEBUGIF
      printf("   test 01: verified passed\n");
  }
  else  {
    test[t++] = false;
    DEBUGIF
      printf("   test 01: verified false\n");  	  
  }

  // [01] ********************************************************

  DEBUGIF
    printf("\n-- test 01: check lists length 0,1,3 and 10 \n");

  DEBUGIF {
    printf("   list r0 ==  0 answer %s\n",osaka_listlength(r0)==0?"true":"false");
    printf("   list r1 ==  1 answer %s\n",osaka_listlength(r1)==1?"true":"false");
    printf("   list r2 ==  3 answer %s\n",osaka_listlength(r2)==3?"true":"false");
    printf("   list r3 == 10 answer %s\n",osaka_listlength(r3)==10?"true":"false");
  }

  test[t++]=osaka_listlength(r0)==0 && 
            osaka_listlength(r1)==1 &&
            osaka_listlength(r2)==3 &&
            osaka_listlength(r3)==10;

  // [02] ********************************************************
  
  DEBUGIF {
    printf("\n-- test 02: verify 0,1,2 and 3 \n");
    printf("   r0 verify answer %s\n",osaka_consistencycheck(r0)?"true":"false");
    printf("   r1 verify answer %s\n",osaka_consistencycheck(r1)?"true":"false");
    printf("   r2 verify answer %s\n",osaka_consistencycheck(r2)?"true":"false");
    printf("   r3 verify answer %s\n",osaka_consistencycheck(r3)?"true":"false");        
  }
  
  test[t++]=osaka_consistencycheck(r0) &&
            osaka_consistencycheck(r1) &&
            osaka_consistencycheck(r2) &&
            osaka_consistencycheck(r3);
        
  // [03] ********************************************************
  
  DEBUGIF {
    printf("\n-- test 03: printall 0,1,2 and 3 \n");
    printf("\n+ [r0]\n");
    osaka_prefix_mapto(r0,osaka_printnode);
    printf("\n+ [r1]\n");
    osaka_prefix_mapto(r1,osaka_printnode);
    printf("\n+ [r2]\n");
    osaka_prefix_mapto(r2,osaka_printnode);
    printf("\n+ [r3]\n");
    osaka_prefix_mapto(r3,osaka_printnode);
  }

  test[t++]=true;

  // [04] ********************************************************

  x0=osaka_serialize(r0,"tmp0.dat");
  x1=osaka_serialize(r1,"tmp1.dat");
  x2=osaka_serialize(r2,"tmp2.dat");
  x3=osaka_serialize(r3,"tmp3.dat");
    
  DEBUGIF {
    printf("\n-- test 04: serialize 0,1,2 and 3 \n");
    printf("   serialized: %d==%d\n",x0,osaka_listlength(r0));
    printf("   serialized: %d==%d\n",x1,osaka_listlength(r1));
    printf("   serialized: %d==%d\n",x2,osaka_listlength(r2));
    printf("   serialized: %d==%d\n",x3,osaka_listlength(r3));
  }
  
  test[t++]=x0==osaka_listlength(r0) &&
            x1==osaka_listlength(r1) &&
            x2==osaka_listlength(r2) &&
            x3==osaka_listlength(r3);

  // [05] ********************************************************

  c0=osaka_deserialize("tmp0.dat");
  c1=osaka_deserialize("tmp1.dat");
  c2=osaka_deserialize("tmp2.dat");
  c3=osaka_deserialize("tmp3.dat");

  DEBUGIF {
    printf("\n-- test 05: deserialize 0,1,2 and 3 \n");
    printf("   deserialized:  0==%d\n",osaka_listlength(c0));
    printf("   deserialized:  1==%d\n",osaka_listlength(c1));
    printf("   deserialized:  3==%d\n",osaka_listlength(c2));
    printf("   deserialized: 10==%d\n",osaka_listlength(c3));
  }
  
  test[t++]= 0==osaka_listlength(c0) &&
            1==osaka_listlength(c1) &&
            3==osaka_listlength(c2) &&
            10==osaka_listlength(c3);

  // [06] ********************************************************
        
  b0=osaka_compare(c0,r0);
  b1=osaka_compare(c1,r1);
  b2=osaka_compare(c2,r2);
  b3=osaka_compare(c3,r3);
        
  DEBUGIF {
    printf("\n-- test 06: compare 0,1,2 and 3 \n");
    printf("   compare: c0==r0 %s\n",b0?"true":"false");
    printf("   compare: c1==r1 %s\n",b1?"true":"false");
    printf("   compare: c2==r2 %s\n",b2?"true":"false");
    printf("   compare: c3==r3 %s\n",b3?"true":"false");
  }

  test[t++]= b0 && b1 && b2 && b3;

  // [07] ********************************************************

  c0=osaka_freelist(c0);
  c1=osaka_freelist(c1);
  c2=osaka_freelist(c2);
  c3=osaka_freelist(c3);

  DEBUGIF {
    printf("\n-- test 07: free using mapto on 0,1,2 and 3 \n");
    printf("    successful\n");
  }
  
  test[t++]=c0==NULL &&
            c1==NULL && 
            c2==NULL &&
            c3==NULL;
         
  // [08] ********************************************************

  b0=osaka_compare(c0,r0);
  b1=osaka_compare(c1,r1);
  b2=osaka_compare(c2,r2);
  b3=osaka_compare(c3,r3);

  test[t++]=b0 && !b1 && !b2 && !b3;

  DEBUGIF {
    printf("\n-- test 08: compare NULL with r0,r1,r2 and r3 \n");
    printf("   compare: c0==r0 %s\n",b0?"true":"false");
    printf("   compare: c1==r1 %s\n",b1?"true":"false");
    printf("   compare: c2==r2 %s\n",b2?"true":"false");
    printf("   compare: c3==r3 %s\n",b3?"true":"false");
  }

  // [09] ********************************************************
  
  c0=osaka_copylist(r0);
  c1=osaka_copylist(r1);
  c2=osaka_copylist(r2);
  c3=osaka_copylist(r3);

  b0=osaka_compare(c0,r0);
  b1=osaka_compare(c1,r1);
  b2=osaka_compare(c2,r2);
  b3=osaka_compare(c3,r3);
        
  test[t++]=b0 && b1 && b2 && b3;

  DEBUGIF {
    printf("\n-- test 09: copy and compare 0,1,2 and 3 \n");
    printf("   compare: c0==r0 %s\n",b0?"true":"false");
    printf("   compare: c1==r1 %s\n",b1?"true":"false");
    printf("   compare: c2==r2 %s\n",b2?"true":"false");
    printf("   compare: c3==r3 %s\n",b3?"true":"false");
  }
  
  c0=osaka_freelist(c0);
  c1=osaka_freelist(c1);
  c2=osaka_freelist(c2);
  c3=osaka_freelist(c3);
  
  // ***************************************************************

  r0=osaka_freelist(r0);
  r1=osaka_freelist(r1);
  r2=osaka_freelist(r2);
  r3=osaka_freelist(r3);

  for(i=0; i<t; i++)  {
    if (!test[i]) {
      printf("-- test[%d] : %s\n", i, test[i]?"true":"false");
    }
  }

  return  test[0] && 
          test[1] && 
          test[2] && 
          test[3] && 
          test[4] && 
          test[5] && 
          test[6] &&
          test[7] &&
          test[8] &&
          test[9] ;
}