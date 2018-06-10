function ord = insertionSort(x)
  n=length(x);
  for i=2:n
    d=i;
    while((d>1) && (x(d)<x(d-1)))
      temp=x(d);
      x(d)=x(d-1);
      x(d-1)=temp;
      d=d-1;
    end
  end
  ord=x;
  %disp(['Vetor ordenado: ' num2str(x)]);
end