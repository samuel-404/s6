#include <stdio.h>
void main()
{
        int in, leakrate, bsize, n, bucket_storage=0,temp;
        printf("Enter the bucket size: \t");
        scanf("%d",&bsize);
        printf("Enter no of inputs: \t");
        scanf("%d",&n);
        printf("Enter the package outgoing rate:  \t");
        scanf("%d",&leakrate);
        printf("Initially Bucket status:contains %d out of %d\n",bucket_storage,bsize);
        while(n!=0)
        {
                printf("\n Enter the incoming packet size: \n");
                scanf("%d",&in);
                printf("Incoming packet size is %d\n",in);
                if(in<=(bsize - bucket_storage))
                {
                        bucket_storage = bucket_storage + in;
                        printf("Bucket status:contains %d out of %d\n",bucket_storage,bsize);
                }
                else
                {
                        printf("Dropped packets:%d\n",in - (bsize-bucket_storage));
                        bucket_storage = bsize;
                        printf("Bucket status:contains %d out of %d\n",bucket_storage,bsize);
                }
                if (bucket_storage >= leakrate)
                {
                        bucket_storage = bucket_storage - leakrate;
                        printf("%d packets transmitted...\n  Bucket status: contains %d packets out of %d\n",leakrate, bucket_storage, bsize);
                }
                else
                {
                        printf("%d packet transmitted...\n  Bucket status: contains 0 packets out of %d\n", bucket_storage,bsize);
                        bucket_storage = 0;
                }
                n--;
        }
        while(bucket_storage>0)
        {
                if (bucket_storage >= leakrate)
                {
                        bucket_storage = bucket_storage - leakrate;
                        printf("%d packets transmitted...\n Bucket status: contains %d packets out of %d\n",leakrate,bucket_storage,bsize);
                }
                else
                {
                        printf("%d packet transmitted...\n  Bucket status: contains 0 packets out of %d\n",bucket_storage,bsize);
                        bucket_storage = 0;
                }
        }
}

