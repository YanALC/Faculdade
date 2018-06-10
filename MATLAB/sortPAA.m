i=1;
time=[];
time2=[];
for i2=100:100:10000
  x=randperm(10000,i2);
  tic;
  insertionSort(x);
  t=toc;
  time(1,i)=t;
  tic;
  intercalationSort(x);
  t2=toc;
  time2(1,i)=t2;
  clear x;
  clear t;
  clear t2;
  i=i+1;
end
i2=(100:100:10000);
plot(i2,time,'b-',i2,time2,'r-');