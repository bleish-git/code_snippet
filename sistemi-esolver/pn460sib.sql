SELECT T2.DataRegistrazione AS [DataRegistrazione]
	,T2.NumRegistraz AS [NumRegistraz]
	,T3.RifLottoAlfanum AS [RifLottoAlfanum]
	,T1.CodArt AS [CodArt]
	,T1.DesArt AS [DesArt]
	,T1.UnitaMisura AS [UnitaMisura]
	,T1.Quantita AS [Quantita]
	,T5.IdDocumento AS [IdDocumentoMat]
	,T5.IdRigaDoc AS [IdRigaDocMat]
	,T5.NumProgrRiga AS [NumProgrRigaMat]
	,T5.NumPosComponente AS [NumPosComponente]
	,T5.CodArt AS [CodArtMat]
	,T5.Des AS [Des]
	,T7.RifLottoAlfanum AS [RifLottoAlfanumMat]
	,T5.UnitaMisura AS [UnitaMisuraMat]
	,T5.Quantita AS [QuantitaMat]
	,Q_RATIO.ratio AS [ratio]
	,Q_RATIO.RappScarico AS [RappScarico]
	,Q_RATIO.Flag AS [Flag]
	,T2.NumDocOriginale AS [NumDocOriginale]
	,'RIG' AS [TESRIG]
	,CASE 
		WHEN (
				DENSE_RANK() OVER (
					PARTITION BY (
						CASE 
							WHEN ISNUMERIC(T1.NotaInterna) > 0
								THEN CONVERT(DECIMAL(15, 5), T1.NotaInterna)
							ELSE 0
							END
						) ORDER BY (T2.NumRegistraz)
					)
				) = 1
			THEN ''
		ELSE CONVERT(VARCHAR(255), (
					DENSE_RANK() OVER (
						PARTITION BY (
							CASE 
								WHEN ISNUMERIC(T1.NotaInterna) > 0
									THEN CONVERT(DECIMAL(15, 5), T1.NotaInterna)
								ELSE 0
								END
							) ORDER BY (T2.NumRegistraz)
						)
					))
		END AS [App]
	,CASE 
		WHEN ISNUMERIC(T1.NotaInterna) > 0
			THEN CONVERT(DECIMAL(15, 5), T1.NotaInterna)
		ELSE 0
		END AS [OdP]
	,CASE 
		WHEN (LEFT(ISNULL(T5.CodArt, ''), 3)) = 'ZFE'
			THEN ISNULL(T5.Quantita, 0.0000)
		ELSE CASE 
				WHEN ISNUMERIC(ISNULL(T6.ValoreCampo14, '')) > 0
					THEN CONVERT(DECIMAL(15, 5), ISNULL(T6.ValoreCampo14, ''))
				ELSE 0
				END
		END AS [QProdotta]
	,CASE 
		WHEN ISNUMERIC(ISNULL(T6.ValoreCampo15, '')) > 0
			THEN CONVERT(DECIMAL(15, 5), ISNULL(T6.ValoreCampo15, ''))
		ELSE 0
		END AS [Qesubero]
	,CASE 
		WHEN ISNUMERIC(ISNULL(T6.ValoreCampo24, '')) > 0
			THEN CONVERT(DECIMAL(15, 5), ISNULL(T6.ValoreCampo24, ''))
		ELSE 0
		END AS [QesuberoEU]
	,CASE 
		WHEN ISNUMERIC(ISNULL(T6.ValoreCampo16, '')) > 0
			THEN CONVERT(DECIMAL(15, 5), ISNULL(T6.ValoreCampo16, ''))
		ELSE 0
		END AS [QCamp]
	,CASE 
		WHEN ISNUMERIC(ISNULL(T6.ValoreCampo17, '')) > 0
			THEN CONVERT(DECIMAL(15, 5), ISNULL(T6.ValoreCampo17, ''))
		ELSE 0
		END AS [QAltriCamp]
	,CASE 
		WHEN (LEFT(ISNULL(T5.CodArt, ''), 3)) = 'ZFE'
			THEN ISNULL(T5.Quantita, 0.0000)
		ELSE (
				CASE 
					WHEN (LEFT(ISNULL(T5.CodArt, ''), 3)) = 'ZFE'
						THEN ISNULL(T5.Quantita, 0.0000)
					ELSE CASE 
							WHEN ISNUMERIC(ISNULL(T6.ValoreCampo14, '')) > 0
								THEN CONVERT(DECIMAL(15, 5), ISNULL(T6.ValoreCampo14, ''))
							ELSE 0
							END
					END
				) + (
				CASE 
					WHEN ISNUMERIC(ISNULL(T6.ValoreCampo17, '')) > 0
						THEN CONVERT(DECIMAL(15, 5), ISNULL(T6.ValoreCampo17, ''))
					ELSE 0
					END
				)
		END AS [QConsumata]
	,ROUND((
			CASE 
				WHEN (LEFT(ISNULL(T5.CodArt, ''), 3)) = 'ZFE'
					THEN ISNULL(T5.Quantita, 0.0000)
				ELSE (
						CASE 
							WHEN (LEFT(ISNULL(T5.CodArt, ''), 3)) = 'ZFE'
								THEN ISNULL(T5.Quantita, 0.0000)
							ELSE CASE 
									WHEN ISNUMERIC(ISNULL(T6.ValoreCampo14, '')) > 0
										THEN CONVERT(DECIMAL(15, 5), ISNULL(T6.ValoreCampo14, ''))
									ELSE 0
									END
							END
						) + (
						CASE 
							WHEN ISNUMERIC(ISNULL(T6.ValoreCampo17, '')) > 0
								THEN CONVERT(DECIMAL(15, 5), ISNULL(T6.ValoreCampo17, ''))
							ELSE 0
							END
						)
				END
			), 0, 1) * ISNULL(Q_RATIO.ratio, 0.000000) AS [QdaScaricare]
FROM DocUniRigheDdtAcq AS [T1] WITH (NOLOCK)
INNER JOIN DocElencoGen AS [T2] WITH (NOLOCK) ON (
		T2.IdDocumento = T1.IdDocumento
		AND (T2.DBGruppo = T1.DBGruppo)
		)
INNER JOIN DocRigheRifLotti AS [T3] WITH (NOLOCK) ON (
		T3.IdDocumento = T1.IdDocumento
		AND T3.IdRigaDoc = T1.IdRigaDoc
		AND T3.CodArt = T1.CodArt
		AND (T3.DBGruppo = T1.DBGruppo)
		)
INNER JOIN DocMagTestata AS [T4] WITH (NOLOCK) ON (
		T4.NumRegistraz = (
			CASE 
				WHEN ISNUMERIC(T1.NotaInterna) > 0
					THEN CONVERT(DECIMAL(15, 5), T1.NotaInterna)
				ELSE 0
				END
			)
		AND T4.CodSerie = 7
		AND (T4.DBGruppo = T1.DBGruppo)
		)
LEFT OUTER JOIN DocMagRighe AS [T5] WITH (NOLOCK) ON (
		T5.IdDocumento = T4.IdDocumento
		AND T5.NumPosComponente = 0.00
		AND (T5.DBGruppo = T4.DBGruppo)
		)
LEFT OUTER JOIN CampiUtenteTabValori AS [T6] WITH (NOLOCK) ON (
		T6.IdDocumento = T5.IdDocumento
		AND T6.IdRigaDoc = T5.IdRigaDoc
		AND (T6.DBGruppo = T5.DBGruppo)
		)
LEFT OUTER JOIN DocRigheRifLotti AS [T7] WITH (NOLOCK) ON (
		T7.IdDocumento = T5.IdDocumento
		AND T7.IdRigaDoc = T5.IdRigaDoc
		AND (T7.DBGruppo = T5.DBGruppo)
		)
LEFT OUTER JOIN (
	SELECT T1.DBGruppo AS [DBGruppo]
		,T2.NumRegistraz AS [NumRegistraz]
		,T1.Quantita AS [Quantita]
		,T4.CodArt AS [CodArt]
		,ISNULL(T5.ValoreCampo14, '') AS [ValoreCampo14]
		,ISNULL(T5.ValoreCampo17, '') AS [ValoreCampo17]
		,CASE 
			WHEN ISNUMERIC(T1.NotaInterna) > 0
				THEN CONVERT(DECIMAL(15, 5), T1.NotaInterna)
			ELSE 0
			END AS [OdP]
		,CASE 
			WHEN ISNUMERIC(ISNULL(T5.ValoreCampo14, '')) > 0
				THEN CONVERT(DECIMAL(15, 5), ISNULL(T5.ValoreCampo14, ''))
			ELSE 0
			END + CASE 
			WHEN ISNUMERIC(ISNULL(T5.ValoreCampo17, '')) > 0
				THEN CONVERT(DECIMAL(15, 5), ISNULL(T5.ValoreCampo17, ''))
			ELSE 0
			END AS [Qscar]
		,T1.Quantita / (
			CASE 
				WHEN ISNUMERIC(ISNULL(T5.ValoreCampo14, '')) > 0
					THEN CONVERT(DECIMAL(15, 5), ISNULL(T5.ValoreCampo14, ''))
				ELSE 0
				END + CASE 
				WHEN ISNUMERIC(ISNULL(T5.ValoreCampo17, '')) > 0
					THEN CONVERT(DECIMAL(15, 5), ISNULL(T5.ValoreCampo17, ''))
				ELSE 0
				END
			) AS [ratio]
		,SUM((
				T1.Quantita / (
					CASE 
						WHEN ISNUMERIC(ISNULL(T5.ValoreCampo14, '')) > 0
							THEN CONVERT(DECIMAL(15, 5), ISNULL(T5.ValoreCampo14, ''))
						ELSE 0
						END + CASE 
						WHEN ISNUMERIC(ISNULL(T5.ValoreCampo17, '')) > 0
							THEN CONVERT(DECIMAL(15, 5), ISNULL(T5.ValoreCampo17, ''))
						ELSE 0
						END
					)
				)) OVER (
			PARTITION BY (
				CASE 
					WHEN ISNUMERIC(T1.NotaInterna) > 0
						THEN CONVERT(DECIMAL(15, 5), T1.NotaInterna)
					ELSE 0
					END
				)
			) AS [Qtemp]
		,CASE 
			WHEN (
					SUM((
							T1.Quantita / (
								CASE 
									WHEN ISNUMERIC(ISNULL(T5.ValoreCampo14, '')) > 0
										THEN CONVERT(DECIMAL(15, 5), ISNULL(T5.ValoreCampo14, ''))
									ELSE 0
									END + CASE 
									WHEN ISNUMERIC(ISNULL(T5.ValoreCampo17, '')) > 0
										THEN CONVERT(DECIMAL(15, 5), ISNULL(T5.ValoreCampo17, ''))
									ELSE 0
									END
								)
							)) OVER (
						PARTITION BY (
							CASE 
								WHEN ISNUMERIC(T1.NotaInterna) > 0
									THEN CONVERT(DECIMAL(15, 5), T1.NotaInterna)
								ELSE 0
								END
							)
						)
					) = 1.000000
				THEN (
						SUM((
								T1.Quantita / (
									CASE 
										WHEN ISNUMERIC(ISNULL(T5.ValoreCampo14, '')) > 0
											THEN CONVERT(DECIMAL(15, 5), ISNULL(T5.ValoreCampo14, ''))
										ELSE 0
										END + CASE 
										WHEN ISNUMERIC(ISNULL(T5.ValoreCampo17, '')) > 0
											THEN CONVERT(DECIMAL(15, 5), ISNULL(T5.ValoreCampo17, ''))
										ELSE 0
										END
									)
								)) OVER (
							PARTITION BY (
								CASE 
									WHEN ISNUMERIC(T1.NotaInterna) > 0
										THEN CONVERT(DECIMAL(15, 5), T1.NotaInterna)
									ELSE 0
									END
								)
							)
						)
			WHEN (
					SUM((
							T1.Quantita / (
								CASE 
									WHEN ISNUMERIC(ISNULL(T5.ValoreCampo14, '')) > 0
										THEN CONVERT(DECIMAL(15, 5), ISNULL(T5.ValoreCampo14, ''))
									ELSE 0
									END + CASE 
									WHEN ISNUMERIC(ISNULL(T5.ValoreCampo17, '')) > 0
										THEN CONVERT(DECIMAL(15, 5), ISNULL(T5.ValoreCampo17, ''))
									ELSE 0
									END
								)
							)) OVER (
						PARTITION BY (
							CASE 
								WHEN ISNUMERIC(T1.NotaInterna) > 0
									THEN CONVERT(DECIMAL(15, 5), T1.NotaInterna)
								ELSE 0
								END
							)
						)
					) > 0.996000
				AND (
					SUM((
							T1.Quantita / (
								CASE 
									WHEN ISNUMERIC(ISNULL(T5.ValoreCampo14, '')) > 0
										THEN CONVERT(DECIMAL(15, 5), ISNULL(T5.ValoreCampo14, ''))
									ELSE 0
									END + CASE 
									WHEN ISNUMERIC(ISNULL(T5.ValoreCampo17, '')) > 0
										THEN CONVERT(DECIMAL(15, 5), ISNULL(T5.ValoreCampo17, ''))
									ELSE 0
									END
								)
							)) OVER (
						PARTITION BY (
							CASE 
								WHEN ISNUMERIC(T1.NotaInterna) > 0
									THEN CONVERT(DECIMAL(15, 5), T1.NotaInterna)
								ELSE 0
								END
							)
						)
					) < 1.004000
				THEN 1
			ELSE (
					SUM((
							T1.Quantita / (
								CASE 
									WHEN ISNUMERIC(ISNULL(T5.ValoreCampo14, '')) > 0
										THEN CONVERT(DECIMAL(15, 5), ISNULL(T5.ValoreCampo14, ''))
									ELSE 0
									END + CASE 
									WHEN ISNUMERIC(ISNULL(T5.ValoreCampo17, '')) > 0
										THEN CONVERT(DECIMAL(15, 5), ISNULL(T5.ValoreCampo17, ''))
									ELSE 0
									END
								)
							)) OVER (
						PARTITION BY (
							CASE 
								WHEN ISNUMERIC(T1.NotaInterna) > 0
									THEN CONVERT(DECIMAL(15, 5), T1.NotaInterna)
								ELSE 0
								END
							)
						)
					)
			END AS [RappScarico]
		,CASE 
			WHEN (
					SUM((
							T1.Quantita / (
								CASE 
									WHEN ISNUMERIC(ISNULL(T5.ValoreCampo14, '')) > 0
										THEN CONVERT(DECIMAL(15, 5), ISNULL(T5.ValoreCampo14, ''))
									ELSE 0
									END + CASE 
									WHEN ISNUMERIC(ISNULL(T5.ValoreCampo17, '')) > 0
										THEN CONVERT(DECIMAL(15, 5), ISNULL(T5.ValoreCampo17, ''))
									ELSE 0
									END
								)
							)) OVER (
						PARTITION BY (
							CASE 
								WHEN ISNUMERIC(T1.NotaInterna) > 0
									THEN CONVERT(DECIMAL(15, 5), T1.NotaInterna)
								ELSE 0
								END
							)
						)
					) = 1.000000
				THEN ''
			WHEN (
					SUM((
							T1.Quantita / (
								CASE 
									WHEN ISNUMERIC(ISNULL(T5.ValoreCampo14, '')) > 0
										THEN CONVERT(DECIMAL(15, 5), ISNULL(T5.ValoreCampo14, ''))
									ELSE 0
									END + CASE 
									WHEN ISNUMERIC(ISNULL(T5.ValoreCampo17, '')) > 0
										THEN CONVERT(DECIMAL(15, 5), ISNULL(T5.ValoreCampo17, ''))
									ELSE 0
									END
								)
							)) OVER (
						PARTITION BY (
							CASE 
								WHEN ISNUMERIC(T1.NotaInterna) > 0
									THEN CONVERT(DECIMAL(15, 5), T1.NotaInterna)
								ELSE 0
								END
							)
						)
					) > 1.004000
				THEN 'X'
			ELSE ''
			END AS [Flag]
	FROM DocUniRigheDdtAcq AS [T1] WITH (NOLOCK)
	INNER JOIN DocElencoGen AS [T2] WITH (NOLOCK) ON (
			T2.IdDocumento = T1.IdDocumento
			AND (T2.DBGruppo = T1.DBGruppo)
			)
	INNER JOIN DocMagTestata AS [T3] WITH (NOLOCK) ON (
			T3.NumRegistraz = (
				CASE 
					WHEN ISNUMERIC(T1.NotaInterna) > 0
						THEN CONVERT(DECIMAL(15, 5), T1.NotaInterna)
					ELSE 0
					END
				)
			AND T3.CodSerie = 7
			AND (T3.DBGruppo = T1.DBGruppo)
			)
	INNER JOIN DocMagRighe AS [T4] WITH (NOLOCK) ON (
			T4.IdDocumento = T3.IdDocumento
			AND (T4.DBGruppo = T3.DBGruppo)
			)
	RIGHT OUTER JOIN CampiUtenteTabValori AS [T5] WITH (NOLOCK) ON (
			T5.IdDocumento = T4.IdDocumento
			AND T5.IdRigaDoc = T4.IdRigaDoc
			AND 0.00 = T4.NumPosComponente
			AND (T5.DBGruppo = T4.DBGruppo)
			)
	WHERE (
			(T4.CodArt LIKE 'ZET%')
			OR (T4.CodArt LIKE 'ZTW%')
			OR (T4.CodArt LIKE 'ZSC%')
			)
	) AS [Q_RATIO] ON (
		Q_RATIO.OdP = (
			CASE 
				WHEN ISNUMERIC(T1.NotaInterna) > 0
					THEN CONVERT(DECIMAL(15, 5), T1.NotaInterna)
				ELSE 0
				END
			)
		AND Q_RATIO.NumRegistraz = T2.NumRegistraz
		AND (Q_RATIO.DBGruppo = T2.DBGruppo)
		)
INNER JOIN DocElencoGen AS [T8] WITH (NOLOCK) ON (
		T8.IdDocumento = T5.IdDocumento
		AND (T8.DBGruppo = T5.DBGruppo)
		)
WHERE (
		(
			(T2.CodCliFor = 10106)
			AND (
				CASE 
					WHEN ISNUMERIC(T1.NotaInterna) > 0
						THEN CONVERT(DECIMAL(15, 5), T1.NotaInterna)
					ELSE 0
					END BETWEEN 3000000
					AND 9999999
				)
			AND (
				(T2.DataRegistrazione >= CONVERT(DATETIME, CONVERT(VARCHAR(10), GETDATE(), 120), 120))
				OR (ISNULL(T8.FirmaUltVarData, {d '1800-01-01' }) >= CONVERT(DATETIME, CONVERT(VARCHAR(10), GETDATE(), 120), 120))
				)
			AND (
				ROUND((
						CASE 
							WHEN (LEFT(ISNULL(T5.CodArt, ''), 3)) = 'ZFE'
								THEN ISNULL(T5.Quantita, 0.0000)
							ELSE (
									CASE 
										WHEN (LEFT(ISNULL(T5.CodArt, ''), 3)) = 'ZFE'
											THEN ISNULL(T5.Quantita, 0.0000)
										ELSE CASE 
												WHEN ISNUMERIC(ISNULL(T6.ValoreCampo14, '')) > 0
													THEN CONVERT(DECIMAL(15, 5), ISNULL(T6.ValoreCampo14, ''))
												ELSE 0
												END
										END
									) + (
									CASE 
										WHEN ISNUMERIC(ISNULL(T6.ValoreCampo17, '')) > 0
											THEN CONVERT(DECIMAL(15, 5), ISNULL(T6.ValoreCampo17, ''))
										ELSE 0
										END
									)
							END
						), 0, 1) * ISNULL(Q_RATIO.ratio, 0.000000) <> 0
				)
			)
		)
	AND (T1.DBGruppo = 'XS')
ORDER BY [OdP] DESC
	,[App] ASC
	,[NumPosComponente] ASC