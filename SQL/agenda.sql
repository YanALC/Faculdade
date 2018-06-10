-- Modelo Lógico:

--CodigoPostal(CodPostal, Logradouro, Estado, Cidade)

--Categoria(CodCategoria, Descrição)

--Contato(CodContato, Nome, Email, Telefone, Idade, Sexo, CodPostal, CodCategoria)
--CodPostal referencia CodigoPostal
--CodCategoria referencia Categoria

-- Tabelas:

CREATE DATABASE Agenda;

CREATE TABLE CodigoPostal (
	codPostal INTEGER PRIMARY KEY,
	logradouro VARCHAR(30) NOT NULL,
	cidade VARCHAR(30) NOT NULL,
	estado CHAR(2) NOT NULL CHECK(estado IN('GO','SP','RJ','TO',’,’RS’))
	);

CREATE TABLE Categoria (
	codCateg INTEGER PRIMARY KEY,
	descricao VARCHAR(30) NOT NULL UNIQUE
	);

CREATE TABLE Contato (
	codContato INTEGER PRIMARY KEY,
	nome VARCHAR(50) NOT NULL,
	telefone INTEGER NOT NULL,
	email VARCHAR(50) UNIQUE NOT NULL,
	sexo CHAR(1) NOT NULL CHECK(sexo IN('M','F','m','f')),
	idade INTEGER NOT NULL CHECK(idade BETWEEN 5 AND 120),
	codPostal INTEGER NOT NULL,
	codCateg INTEGER NOT NULL,
	FOREIGN KEY(codPostal) references CODPOSTAL(codPostal),
	FOREIGN KEY(codCat) references CATEGORIA(codCateg)
	);

-- Dados: CodigoPostal(4), Categoria(4), Contato(10)

--CodigoPostal
INSERT INTO CodigoPostal VALUES (12345, 'Rua Pimentel', 'Goiânia', 'GO');
INSERT INTO CodigoPostal VALUES (54321, 'Avenida Paulista', 'São Paulo', 'SP');
INSERT INTO CodigoPostal VALUES (55555, 'Rua 345', 'Palmas', 'TO');
INSERT INTO CodigoPostal VALUES (56789, 'Rua Pedro Ludovico', 'Rio de Janeiro', 'RJ');
INSERT INTO CodigoPostal VALUES (74123, 'Rua teste', 'Porto Alegre', 'RS');

--Categoria
INSERT INTO Categoria VALUES (00001 'Família') ;
INSERT INTO Categoria VALUES (00002, 'Amigos') ;
INSERT INTO Categoria VALUES (00003, 'Faculdade') ;
INSERT INTO Categoria VALUES (00004, 'Trabalho');
INSERT INTO Categoria VALUES (100, 'Sem Categoria');

--Contato
INSERT INTO Contato VALUES (11111, 'Yan', 98787548, 'yan@email', 'M', 19, 12345, 100);
INSERT INTO Contato VALUES (22222, 'Carlos', 6240028922, 'carlos@email', 'M', 52, 74123, 00004);
INSERT INTO Contato VALUES (33333, 'Gabriela', 1165456744, 'gabriela@email', 'F', 23, 56789, 00003) ; 
INSERT INTO Contato VALUES (44444, 'Matheus', 1365564520, 'matheus@email', 'M', 34, 54321, 00002) ;
INSERT INTO Contato VALUES (55555, 'Pedro', 4398433530, 'pedro@email', 'M', 21, 55555, 00002) ;
INSERT INTO Contato VALUES (66666, 'Antonio', 4567876787, 'antonio@email', 'M', 45, 54321, 00001) ;
INSERT INTO Contato VALUES (77777, 'Ana', 6289898989, 'ana@email', 'F', 10, 12345, 00003) ;
INSERT INTO Contato VALUES (88888, 'Arthur Ricardo', 123423423, 'arthur@email', 'M', 21, 12345, 00003);
INSERT INTO Contato VALUES (99999, 'João', 146456564, 'joao@email', 'M', 43, 55555, 00001);
INSERT INTO Contato VALUES (01010, 'Daniel', 325454656, 'arthur@email', 'M', 10, 74123, 100);
