%% Função que resolve sistemas lineares de qualquer tipo através do Método de Gauss
function b = gauss(A,b)
n = length(b);
%-----------------Elimination phase-------------
for k = 1:n-1
    for i = k+1:n
        if A(i,k)~=0 && A(k,k)~=0
            lambda = A(i,k)/A(k,k);
            A(i,k:n) = A(i,k:n) - lambda*A(k,k:n);
            b(i)= b(i) - lambda*b(k);
        end
    end
end
%--------------Back substitution phase-----------
for k = n:-1:1
    if(A(k,k) < 10^-4)
        b(k) = 1;
    else
        b(k) = (b(k) - A(k,k:n)*transpose(b(k:n)))/A(k,k);
    end
end
end