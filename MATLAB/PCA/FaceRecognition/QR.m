function [y,Q,R] = QR(A,k)
n=length(A);
V=A;
Q=zeros(n,n);
R=zeros(n,n);
m=1;
while m>k % precisão
    for i=1:n
		R(i,i)=norm(V(:,i));
		Q(:,i)=V(:,i)/R(i,i);
        for j=(i+1):n
			R(i,j)=Q(:,i)'*V(:,j);
			V(:,j)=V(:,j)-R(i,j)*Q(:,i);
        end
    end
    [~,~,lt]=find((tril(V,-1)));
	m=max(lt);
	V=R*Q;
end
y=diag(V);
end