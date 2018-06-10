CREATE DATABASE Locadora;

-- TABELAS

-- Tabela Cliente
CREATE TABLE Cliente (
	CPF BIGINT PRIMARY KEY,
	Nome VARCHAR(100) NOT NULL,
	Tipo VARCHAR(45) NOT NULL
);

-- Tabela Fatura
CREATE TABLE Fatura (
	Cod_Fatura INTEGER PRIMARY KEY,
	Cliente_CPF BIGINT NOT NULL,
	FOREIGN KEY (Cliente_CPF) REFERENCES Cliente (CPF)
);

-- Tabela Modelo
CREATE TABLE Modelo (
	id_Modelo SERIAL PRIMARY KEY,
	Descricao VARCHAR(90) UNIQUE NOT NULL,
	Marca VARCHAR(45) NOT NULL
);

-- Tabela Categoria
CREATE TABLE Categoria (
	id_Categoria SERIAL PRIMARY KEY,
	Descricao VARCHAR(90) UNIQUE NOT NULL,
	Diaria REAL NOT NULL
);

-- Tabela Automovel
CREATE TABLE Automovel (
	Placa CHAR(8) PRIMARY KEY,
	Modelo_id_Modelo INTEGER NOT NULL,
	Categoria_id_Categoria INTEGER NOT NULL,
	FOREIGN KEY (Modelo_id_Modelo) REFERENCES Modelo (id_Modelo),
	FOREIGN KEY (Categoria_id_Categoria) REFERENCES Categoria (id_Categoria)
);

-- Tabela Locacao
CREATE TABLE Locacao (
	Automovel_Placa CHAR(8) NOT NULL,
	Fatura_Cod_Fatura INTEGER NOT NULL,
	Km_Inicio REAL NOT NULL,
	Km_Final REAL NOT NULL,
	Qtd_Diarias INTEGER NOT NULL,
	PRIMARY KEY (Automovel_Placa, Fatura_Cod_Fatura),
	FOREIGN KEY (Automovel_Placa) REFERENCES Automovel (Placa),
	FOREIGN KEY (Fatura_Cod_Fatura) REFERENCES Fatura (Cod_Fatura)
);


-- DADOS

-- Clientes
INSERT INTO Cliente VALUES
	(123456789,'JOSÉ ANTONIO DA SILVA','VIP'),
	(987654321,'CARLOS DA SILVA MENDES','DIAMANTE'),
	(1123987456,'MARIA SILVA CARVALHO','RUBY'),
	(5436789321,'ANTONIO CARLOS MENDES','RUBY');

-- Faturas
INSERT INTO Fatura VALUES
	(1230,123456789),
	(1330,123456789),
	(3450,123456789),
	(235,123456789),

	(987,987654321),
	(569,987654321),

	(2987,1123987456),
	(23456,1123987456),

	(12987,5436789321),
	(12346,5436789321),
	(56435,5436789321);

-- Modelos
INSERT INTO Modelo VALUES
	(DEFAULT, 'GOL', 'VOLKSWAGEN'),--Codigo=1
	(DEFAULT, 'COBALT', 'GM'),--Codigo=2
	(DEFAULT, 'CAPTIVA', 'GM'),--Codigo=3
	(DEFAULT, 'SW4', 'TOYOTA'),--Codigo=4
	(DEFAULT, 'C-18', 'MERCEDES'),--Codigo=5
	(DEFAULT, 'V60', 'VOLVO');--Codigo=6

-- Categorias
INSERT INTO Categoria VALUES
	(DEFAULT, 'ECÔNOMICO', 65.00),--Codigo=1
	(DEFAULT, 'INTERMEDIÁRIO', 75.00),--Codigo=2
	(DEFAULT, 'SUV', 110.00),--Codigo=3
	(DEFAULT, 'EXECUTIVO', 250.00);--Codigo=4

-- Automóveis
INSERT INTO Automovel VALUES
	('ABC-1234', 1, 1),
	('JCW-4321', 2, 2),
	('ASD-3456', 3, 3),
	('WER-5678', 4, 3),
	('QWS-1234', 5, 4),
	('QAS-1256', 6, 4),
	('KOP-1256', 6, 4),
	('RNU-3456', 2, 2),
	('TRB-1234', 5, 4);

-- Locações
INSERT INTO Locacao VALUES
--Jose
	('ABC-1234', 1230, 1000, 1700, 5),
	('JCW-4321', 1330, 13450, 14560, 8),
	('ASD-3456', 3450, 23459, 28450, 4),
	('WER-5678', 3450, 4578, 6570, 6),
	('QWS-1234', 235, 3240, 5689, 7),
--Carlos
	('QAS-1256',	987, 1000, 1500, 6),
	('QWS-1234',	987, 1000, 1350, 4),
	('ASD-3456',	569, 1290, 1590, 3),
--Maria
	('KOP-1256', 2987, 21350, 25500, 8),
	('RNU-3456', 2987, 21290, 21590, 5),
	('TRB-1234', 23456, 21000, 21350, 7),
--Antonio
	('KOP-1256', 12987, 31350,	45500, 18),
	('RNU-3456', 12346, 31290,	41590, 15),
	('TRB-1234', 56435, 31000,	41350, 17);
