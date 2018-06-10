CREATE DEFINER = CURRENT_USER TRIGGER `mydb`.`Locacao_AFTER_INSERT` AFTER INSERT ON `Locacao` FOR EACH ROW
BEGIN
	UPDATE mydb.Locacao L, mydb.Automovel A
    SET A.KM = A.KM + L.KmRodados
    WHERE L.Automovel_Placa = A.Placa;
END