--
-- PostgreSQL database dump
--

-- Dumped from database version 10.1
-- Dumped by pg_dump version 10.1

-- Started on 2017-12-18 05:08:52

SET statement_timeout = 0;
SET lock_timeout = 0;
SET idle_in_transaction_session_timeout = 0;
SET client_encoding = 'UTF8';
SET standard_conforming_strings = on;
SET check_function_bodies = false;
SET client_min_messages = warning;
SET row_security = off;

--
-- TOC entry 1 (class 3079 OID 12924)
-- Name: plpgsql; Type: EXTENSION; Schema: -; Owner: 
--

CREATE EXTENSION IF NOT EXISTS plpgsql WITH SCHEMA pg_catalog;


--
-- TOC entry 2850 (class 0 OID 0)
-- Dependencies: 1
-- Name: EXTENSION plpgsql; Type: COMMENT; Schema: -; Owner: 
--

COMMENT ON EXTENSION plpgsql IS 'PL/pgSQL procedural language';


SET search_path = public, pg_catalog;

SET default_tablespace = '';

SET default_with_oids = false;

--
-- TOC entry 202 (class 1259 OID 16561)
-- Name: automovel; Type: TABLE; Schema: public; Owner: postgres
--

CREATE TABLE automovel (
    placa character(8) NOT NULL,
    modelo_id_modelo integer NOT NULL,
    categoria_id_categoria integer NOT NULL
);


ALTER TABLE automovel OWNER TO postgres;

--
-- TOC entry 201 (class 1259 OID 16553)
-- Name: categoria; Type: TABLE; Schema: public; Owner: postgres
--

CREATE TABLE categoria (
    id_categoria integer NOT NULL,
    descricao character varying(90) NOT NULL,
    diaria real NOT NULL
);


ALTER TABLE categoria OWNER TO postgres;

--
-- TOC entry 200 (class 1259 OID 16551)
-- Name: categoria_id_categoria_seq; Type: SEQUENCE; Schema: public; Owner: postgres
--

CREATE SEQUENCE categoria_id_categoria_seq
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE categoria_id_categoria_seq OWNER TO postgres;

--
-- TOC entry 2851 (class 0 OID 0)
-- Dependencies: 200
-- Name: categoria_id_categoria_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: postgres
--

ALTER SEQUENCE categoria_id_categoria_seq OWNED BY categoria.id_categoria;


--
-- TOC entry 196 (class 1259 OID 16526)
-- Name: cliente; Type: TABLE; Schema: public; Owner: postgres
--

CREATE TABLE cliente (
    cpf bigint NOT NULL,
    nome character varying(100) NOT NULL,
    tipo character varying(45) NOT NULL
);


ALTER TABLE cliente OWNER TO postgres;

--
-- TOC entry 197 (class 1259 OID 16531)
-- Name: fatura; Type: TABLE; Schema: public; Owner: postgres
--

CREATE TABLE fatura (
    cod_fatura integer NOT NULL,
    cliente_cpf bigint NOT NULL
);


ALTER TABLE fatura OWNER TO postgres;

--
-- TOC entry 203 (class 1259 OID 16576)
-- Name: locacao; Type: TABLE; Schema: public; Owner: postgres
--

CREATE TABLE locacao (
    automovel_placa character(8) NOT NULL,
    fatura_cod_fatura integer NOT NULL,
    kminicio real NOT NULL,
    kmfinal real NOT NULL,
    qtddiarias integer NOT NULL
);


ALTER TABLE locacao OWNER TO postgres;

--
-- TOC entry 199 (class 1259 OID 16543)
-- Name: modelo; Type: TABLE; Schema: public; Owner: postgres
--

CREATE TABLE modelo (
    id_modelo integer NOT NULL,
    descricao character varying(90) NOT NULL,
    marca character varying(45) NOT NULL
);


ALTER TABLE modelo OWNER TO postgres;

--
-- TOC entry 198 (class 1259 OID 16541)
-- Name: modelo_id_modelo_seq; Type: SEQUENCE; Schema: public; Owner: postgres
--

CREATE SEQUENCE modelo_id_modelo_seq
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE modelo_id_modelo_seq OWNER TO postgres;

--
-- TOC entry 2852 (class 0 OID 0)
-- Dependencies: 198
-- Name: modelo_id_modelo_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: postgres
--

ALTER SEQUENCE modelo_id_modelo_seq OWNED BY modelo.id_modelo;


--
-- TOC entry 2693 (class 2604 OID 16556)
-- Name: categoria id_categoria; Type: DEFAULT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY categoria ALTER COLUMN id_categoria SET DEFAULT nextval('categoria_id_categoria_seq'::regclass);


--
-- TOC entry 2692 (class 2604 OID 16546)
-- Name: modelo id_modelo; Type: DEFAULT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY modelo ALTER COLUMN id_modelo SET DEFAULT nextval('modelo_id_modelo_seq'::regclass);


--
-- TOC entry 2842 (class 0 OID 16561)
-- Dependencies: 202
-- Data for Name: automovel; Type: TABLE DATA; Schema: public; Owner: postgres
--

COPY automovel (placa, modelo_id_modelo, categoria_id_categoria) FROM stdin;
ABC-1234	1	1
JCW-4321	2	2
ASD-3456	3	3
WER-5678	4	3
QWS-1234	5	4
QAS-1256	6	4
KOP-1256	6	4
RNU-3456	2	2
TRB-1234	5	4
\.


--
-- TOC entry 2841 (class 0 OID 16553)
-- Dependencies: 201
-- Data for Name: categoria; Type: TABLE DATA; Schema: public; Owner: postgres
--

COPY categoria (id_categoria, descricao, diaria) FROM stdin;
1	ECÔNOMICO	65
2	INTERMEDIÁRIO	75
3	SUV	110
4	EXECUTIVO	250
\.


--
-- TOC entry 2836 (class 0 OID 16526)
-- Dependencies: 196
-- Data for Name: cliente; Type: TABLE DATA; Schema: public; Owner: postgres
--

COPY cliente (cpf, nome, tipo) FROM stdin;
123456789	JOSÉ ANTONIO DA SILVA	VIP
987654321	CARLOS DA SILVA MENDES	DIAMANTE
1123987456	MARIA SILVA CARVALHO	RUBY
5436789321	ANTONIO CARLOS MENDES	RUBY
\.


--
-- TOC entry 2837 (class 0 OID 16531)
-- Dependencies: 197
-- Data for Name: fatura; Type: TABLE DATA; Schema: public; Owner: postgres
--

COPY fatura (cod_fatura, cliente_cpf) FROM stdin;
1230	123456789
1330	123456789
3450	123456789
235	123456789
987	987654321
569	987654321
2987	1123987456
23456	1123987456
12987	5436789321
12346	5436789321
56435	5436789321
\.


--
-- TOC entry 2843 (class 0 OID 16576)
-- Dependencies: 203
-- Data for Name: locacao; Type: TABLE DATA; Schema: public; Owner: postgres
--

COPY locacao (automovel_placa, fatura_cod_fatura, kminicio, kmfinal, qtddiarias) FROM stdin;
ABC-1234	1230	1000	1700	5
JCW-4321	1330	13450	14560	8
ASD-3456	3450	23459	28450	4
WER-5678	3450	4578	6570	6
QWS-1234	235	3240	5689	7
QAS-1256	987	1000	1500	6
QWS-1234	987	1000	1350	4
ASD-3456	569	1290	1590	3
KOP-1256	2987	21350	25500	8
RNU-3456	2987	21290	21590	5
TRB-1234	23456	21000	21350	7
KOP-1256	12987	31350	45500	18
RNU-3456	12346	31290	41590	15
TRB-1234	56435	31000	41350	17
\.


--
-- TOC entry 2839 (class 0 OID 16543)
-- Dependencies: 199
-- Data for Name: modelo; Type: TABLE DATA; Schema: public; Owner: postgres
--

COPY modelo (id_modelo, descricao, marca) FROM stdin;
1	GOL	VOLKSWAGEN
2	COBALT	GM
3	CAPTIVA	GM
4	SW4	TOYOTA
5	C-18	MERCEDES
6	V60	VOLVO
\.


--
-- TOC entry 2853 (class 0 OID 0)
-- Dependencies: 200
-- Name: categoria_id_categoria_seq; Type: SEQUENCE SET; Schema: public; Owner: postgres
--

SELECT pg_catalog.setval('categoria_id_categoria_seq', 4, true);


--
-- TOC entry 2854 (class 0 OID 0)
-- Dependencies: 198
-- Name: modelo_id_modelo_seq; Type: SEQUENCE SET; Schema: public; Owner: postgres
--

SELECT pg_catalog.setval('modelo_id_modelo_seq', 6, true);


--
-- TOC entry 2707 (class 2606 OID 16565)
-- Name: automovel automovel_pkey; Type: CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY automovel
    ADD CONSTRAINT automovel_pkey PRIMARY KEY (placa);


--
-- TOC entry 2703 (class 2606 OID 16560)
-- Name: categoria categoria_descricao_key; Type: CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY categoria
    ADD CONSTRAINT categoria_descricao_key UNIQUE (descricao);


--
-- TOC entry 2705 (class 2606 OID 16558)
-- Name: categoria categoria_pkey; Type: CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY categoria
    ADD CONSTRAINT categoria_pkey PRIMARY KEY (id_categoria);


--
-- TOC entry 2695 (class 2606 OID 16530)
-- Name: cliente cliente_pkey; Type: CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY cliente
    ADD CONSTRAINT cliente_pkey PRIMARY KEY (cpf);


--
-- TOC entry 2697 (class 2606 OID 16535)
-- Name: fatura fatura_pkey; Type: CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY fatura
    ADD CONSTRAINT fatura_pkey PRIMARY KEY (cod_fatura);


--
-- TOC entry 2709 (class 2606 OID 16580)
-- Name: locacao locacao_pkey; Type: CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY locacao
    ADD CONSTRAINT locacao_pkey PRIMARY KEY (automovel_placa, fatura_cod_fatura);


--
-- TOC entry 2699 (class 2606 OID 16550)
-- Name: modelo modelo_descricao_key; Type: CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY modelo
    ADD CONSTRAINT modelo_descricao_key UNIQUE (descricao);


--
-- TOC entry 2701 (class 2606 OID 16548)
-- Name: modelo modelo_pkey; Type: CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY modelo
    ADD CONSTRAINT modelo_pkey PRIMARY KEY (id_modelo);


--
-- TOC entry 2712 (class 2606 OID 16571)
-- Name: automovel automovel_categoria_id_categoria_fkey; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY automovel
    ADD CONSTRAINT automovel_categoria_id_categoria_fkey FOREIGN KEY (categoria_id_categoria) REFERENCES categoria(id_categoria);


--
-- TOC entry 2711 (class 2606 OID 16566)
-- Name: automovel automovel_modelo_id_modelo_fkey; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY automovel
    ADD CONSTRAINT automovel_modelo_id_modelo_fkey FOREIGN KEY (modelo_id_modelo) REFERENCES modelo(id_modelo);


--
-- TOC entry 2710 (class 2606 OID 16536)
-- Name: fatura fatura_cliente_cpf_fkey; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY fatura
    ADD CONSTRAINT fatura_cliente_cpf_fkey FOREIGN KEY (cliente_cpf) REFERENCES cliente(cpf);


--
-- TOC entry 2713 (class 2606 OID 16581)
-- Name: locacao locacao_automovel_placa_fkey; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY locacao
    ADD CONSTRAINT locacao_automovel_placa_fkey FOREIGN KEY (automovel_placa) REFERENCES automovel(placa);


--
-- TOC entry 2714 (class 2606 OID 16586)
-- Name: locacao locacao_fatura_cod_fatura_fkey; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY locacao
    ADD CONSTRAINT locacao_fatura_cod_fatura_fkey FOREIGN KEY (fatura_cod_fatura) REFERENCES fatura(cod_fatura);


-- Completed on 2017-12-18 05:08:52

--
-- PostgreSQL database dump complete
--

