function V = PDGrafo(madj)
    V = zeros(lenght(madj),2);
    d = madj;
    %V(lenght(V),2);
    for k=lenght(V):-1:1
        for i=1:
            for j = 1:num_states(k+1)
                path_length(j)= d(k,i,k+1,j)+V(k+1,j);
            end
            V(k,i)=min(path_length);
            clear path_length
        end
    end
end