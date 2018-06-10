function ord = BubbleSort(x)
bubble=length(x);
while(bubble~=1)
    pivo=1;
    for i=2:bubble
        j=i-1;
        if(x(j)>x(i))
            [x(i), x(j)] = deal(x(j),x(i));
            %temp=x(i);
            %x(i)=x(j);
            %x(j)=temp;
            pivo=i;
        end
    end
    bubble=pivo;
end
ord=x;
end