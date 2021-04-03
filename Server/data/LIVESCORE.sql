USE [MASTER]
GO
CREATE DATABASE [DB_LIVESCORE]
GO
USE [DB_LIVESCORE]
GO
/****** Object:  Table [dbo].[DETAILS_CARD]    Script Date: 4/2/2021 4:07:03 PM ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
SET ANSI_PADDING ON
GO
CREATE TABLE [dbo].[DETAILS_CARD](
	[IDMATCH] [varchar](10) NOT NULL,
	[TIMECARD] [varchar](10) NOT NULL,
	[CATEGORY] [varchar](10) NULL,
	[PLAYER_A] [varchar](200) NULL,
	[PLAYER_B] [varchar](200) NULL,
PRIMARY KEY CLUSTERED 
(
	[IDMATCH] ASC,
	[TIMECARD] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON) ON [PRIMARY]
) ON [PRIMARY]

GO
SET ANSI_PADDING OFF
GO
/****** Object:  Table [dbo].[DETAILS_SCORE]    Script Date: 4/2/2021 4:07:03 PM ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
SET ANSI_PADDING ON
GO
CREATE TABLE [dbo].[DETAILS_SCORE](
	[IDMATCH] [varchar](10) NOT NULL,
	[TIMESCORE] [varchar](10) NOT NULL,
	[SCORE_A] [smallint] NULL DEFAULT ((0)),
	[SCORE_B] [smallint] NULL DEFAULT ((0)),
	[PLAYER_A] [varchar](200) NULL,
	[PLAYER_B] [varchar](200) NULL,
PRIMARY KEY CLUSTERED 
(
	[IDMATCH] ASC,
	[TIMESCORE] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON) ON [PRIMARY]
) ON [PRIMARY]

GO
SET ANSI_PADDING OFF
GO
/****** Object:  Table [dbo].[GROUP_MATCH]    Script Date: 4/2/2021 4:07:03 PM ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
SET ANSI_PADDING ON
GO
CREATE TABLE [dbo].[GROUP_MATCH](
	[GROUPID] [varchar](20) NOT NULL,
	[GROUPNAME] [varchar](300) NULL,
PRIMARY KEY CLUSTERED 
(
	[GROUPID] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON) ON [PRIMARY]
) ON [PRIMARY]

GO
SET ANSI_PADDING OFF
GO
/****** Object:  Table [dbo].[MATCH]    Script Date: 4/2/2021 4:07:03 PM ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
SET ANSI_PADDING ON
GO
CREATE TABLE [dbo].[MATCH](
	[ID] [varchar](10) NOT NULL,
	[ID_TEAMA] [varchar](10) NULL,
	[ID_TEAMB] [varchar](10) NULL,
	[ID_GROUP] [varchar](20) NULL,
	[STARTTIME] [datetime] NULL,
	[STATUS_MATCH] [varchar](3) NULL,
PRIMARY KEY CLUSTERED 
(
	[ID] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON) ON [PRIMARY]
) ON [PRIMARY]

GO
SET ANSI_PADDING OFF
GO
/****** Object:  Table [dbo].[TEAM]    Script Date: 4/2/2021 4:07:03 PM ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
SET ANSI_PADDING ON
GO
CREATE TABLE [dbo].[TEAM](
	[IDTEAM] [varchar](10) NOT NULL,
	[NAME] [varchar](50) NULL,
PRIMARY KEY CLUSTERED 
(
	[IDTEAM] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON) ON [PRIMARY]
) ON [PRIMARY]

GO
SET ANSI_PADDING OFF
GO
/****** Object:  Table [dbo].[USERS]    Script Date: 4/2/2021 4:07:03 PM ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
SET ANSI_PADDING ON
GO
CREATE TABLE [dbo].[USERS](
	[USR] [varchar](100) NOT NULL,
	[PWD] [varchar](100) NULL,
	[LOGINSTATUS] [bit] NOT NULL DEFAULT ((0)),
PRIMARY KEY CLUSTERED 
(
	[USR] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON) ON [PRIMARY]
) ON [PRIMARY]

GO
SET ANSI_PADDING OFF
GO
INSERT [dbo].[DETAILS_CARD] ([IDMATCH], [TIMECARD], [CATEGORY], [PLAYER_A], [PLAYER_B]) VALUES (N'AS', N'45+1''', N'YELLOW', NULL, N'Uros Spajic')
INSERT [dbo].[DETAILS_CARD] ([IDMATCH], [TIMECARD], [CATEGORY], [PLAYER_A], [PLAYER_B]) VALUES (N'AS', N'76''', N'YELLOW', NULL, N'Nemanja Gudelj')
INSERT [dbo].[DETAILS_CARD] ([IDMATCH], [TIMECARD], [CATEGORY], [PLAYER_A], [PLAYER_B]) VALUES (N'AS', N'88''', N'YELLOW', N'Tamkin Khalilzade', NULL)
INSERT [dbo].[DETAILS_CARD] ([IDMATCH], [TIMECARD], [CATEGORY], [PLAYER_A], [PLAYER_B]) VALUES (N'CS', N'42''', N'YELLOW', NULL, N'Josip Ilicic')
INSERT [dbo].[DETAILS_CARD] ([IDMATCH], [TIMECARD], [CATEGORY], [PLAYER_A], [PLAYER_B]) VALUES (N'CS', N'47''', N'YELLOW', NULL, N'Jasmin Kurtic')
INSERT [dbo].[DETAILS_CARD] ([IDMATCH], [TIMECARD], [CATEGORY], [PLAYER_A], [PLAYER_B]) VALUES (N'GG', N'15''', N'YELLOW', NULL, N'Giorgi Aburjania')
INSERT [dbo].[DETAILS_CARD] ([IDMATCH], [TIMECARD], [CATEGORY], [PLAYER_A], [PLAYER_B]) VALUES (N'GG', N'59''', N'YELLOW', N'Konstantinos Fortounis', NULL)
INSERT [dbo].[DETAILS_CARD] ([IDMATCH], [TIMECARD], [CATEGORY], [PLAYER_A], [PLAYER_B]) VALUES (N'GG', N'67''', N'YELLOW', NULL, N'Otar Kiteishvili')
INSERT [dbo].[DETAILS_CARD] ([IDMATCH], [TIMECARD], [CATEGORY], [PLAYER_A], [PLAYER_B]) VALUES (N'GG', N'71''', N'YELLOW', N'Kyriakos Papadopoulos', NULL)
INSERT [dbo].[DETAILS_CARD] ([IDMATCH], [TIMECARD], [CATEGORY], [PLAYER_A], [PLAYER_B]) VALUES (N'GG', N'76''', N'YELLOW', N'Georgios Giakoumakis', NULL)
INSERT [dbo].[DETAILS_CARD] ([IDMATCH], [TIMECARD], [CATEGORY], [PLAYER_A], [PLAYER_B]) VALUES (N'GG', N'80''', N'YELLOW', N'Zeca', NULL)
INSERT [dbo].[DETAILS_CARD] ([IDMATCH], [TIMECARD], [CATEGORY], [PLAYER_A], [PLAYER_B]) VALUES (N'GG', N'90+1''', N'YELLOW', NULL, N'Jaba Kankava')
INSERT [dbo].[DETAILS_CARD] ([IDMATCH], [TIMECARD], [CATEGORY], [PLAYER_A], [PLAYER_B]) VALUES (N'GN', N'31''', N'YELLOW', N'Kian Ronan', NULL)
INSERT [dbo].[DETAILS_CARD] ([IDMATCH], [TIMECARD], [CATEGORY], [PLAYER_A], [PLAYER_B]) VALUES (N'GN', N'38''', N'YELLOW', NULL, N'Davy Klaassen')
INSERT [dbo].[DETAILS_CARD] ([IDMATCH], [TIMECARD], [CATEGORY], [PLAYER_A], [PLAYER_B]) VALUES (N'UK', N'36''', N'YELLOW', NULL, N'Aibol Abiken')
INSERT [dbo].[DETAILS_CARD] ([IDMATCH], [TIMECARD], [CATEGORY], [PLAYER_A], [PLAYER_B]) VALUES (N'UK', N'43''', N'YELLOW', NULL, N'Serikzhan Muzhikov')
INSERT [dbo].[DETAILS_CARD] ([IDMATCH], [TIMECARD], [CATEGORY], [PLAYER_A], [PLAYER_B]) VALUES (N'UK', N'6''', N'YELLOW', NULL, N'Nuraly Alip')
INSERT [dbo].[DETAILS_CARD] ([IDMATCH], [TIMECARD], [CATEGORY], [PLAYER_A], [PLAYER_B]) VALUES (N'UK', N'62''', N'YELLOW', NULL, N'Yan Vorogovsky')
INSERT [dbo].[DETAILS_CARD] ([IDMATCH], [TIMECARD], [CATEGORY], [PLAYER_A], [PLAYER_B]) VALUES (N'UK', N'70''', N'YELLOW', N'Oleksandr Zinchenk', NULL)
INSERT [dbo].[DETAILS_CARD] ([IDMATCH], [TIMECARD], [CATEGORY], [PLAYER_A], [PLAYER_B]) VALUES (N'UK', N'89''', N'YELLOW', N'Marlos', NULL)
INSERT [dbo].[DETAILS_CARD] ([IDMATCH], [TIMECARD], [CATEGORY], [PLAYER_A], [PLAYER_B]) VALUES (N'UK', N'90''', N'YELLOW', NULL, N'Stas Pokatilov')
INSERT [dbo].[DETAILS_SCORE] ([IDMATCH], [TIMESCORE], [SCORE_A], [SCORE_B], [PLAYER_A], [PLAYER_B]) VALUES (N'AS', N'16''', 0, 1, NULL, N'Aleksandar Mitrovic')
INSERT [dbo].[DETAILS_SCORE] ([IDMATCH], [TIMESCORE], [SCORE_A], [SCORE_B], [PLAYER_A], [PLAYER_B]) VALUES (N'AS', N'59''', 1, 1, N'Emin Makhmudov', NULL)
INSERT [dbo].[DETAILS_SCORE] ([IDMATCH], [TIMESCORE], [SCORE_A], [SCORE_B], [PLAYER_A], [PLAYER_B]) VALUES (N'AS', N'81''', 1, 2, NULL, N'Aleksandar Mitrovic')
INSERT [dbo].[DETAILS_SCORE] ([IDMATCH], [TIMESCORE], [SCORE_A], [SCORE_B], [PLAYER_A], [PLAYER_B]) VALUES (N'BB', N'14''', 1, 0, N'Michy Batshuayi', NULL)
INSERT [dbo].[DETAILS_SCORE] ([IDMATCH], [TIMESCORE], [SCORE_A], [SCORE_B], [PLAYER_A], [PLAYER_B]) VALUES (N'BB', N'17''', 2, 0, N'Hans Vanaken', NULL)
INSERT [dbo].[DETAILS_SCORE] ([IDMATCH], [TIMESCORE], [SCORE_A], [SCORE_B], [PLAYER_A], [PLAYER_B]) VALUES (N'BB', N'38''', 3, 0, N'Leandro Trossard', NULL)
INSERT [dbo].[DETAILS_SCORE] ([IDMATCH], [TIMESCORE], [SCORE_A], [SCORE_B], [PLAYER_A], [PLAYER_B]) VALUES (N'BB', N'42''', 4, 0, N'Jeremy Doku', NULL)
INSERT [dbo].[DETAILS_SCORE] ([IDMATCH], [TIMESCORE], [SCORE_A], [SCORE_B], [PLAYER_A], [PLAYER_B]) VALUES (N'BB', N'49''', 5, 0, N'Dennis Praet', NULL)
INSERT [dbo].[DETAILS_SCORE] ([IDMATCH], [TIMESCORE], [SCORE_A], [SCORE_B], [PLAYER_A], [PLAYER_B]) VALUES (N'BB', N'70''', 6, 0, N'Christian Benteke', NULL)
INSERT [dbo].[DETAILS_SCORE] ([IDMATCH], [TIMESCORE], [SCORE_A], [SCORE_B], [PLAYER_A], [PLAYER_B]) VALUES (N'BB', N'76''', 7, 0, N'Leandro Trossard', NULL)
INSERT [dbo].[DETAILS_SCORE] ([IDMATCH], [TIMESCORE], [SCORE_A], [SCORE_B], [PLAYER_A], [PLAYER_B]) VALUES (N'BB', N'89''', 8, 0, N'Hans Vanaken', NULL)
INSERT [dbo].[DETAILS_SCORE] ([IDMATCH], [TIMESCORE], [SCORE_A], [SCORE_B], [PLAYER_A], [PLAYER_B]) VALUES (N'CS', N'38''', 1, 0, N'Ioannis Pittas', NULL)
INSERT [dbo].[DETAILS_SCORE] ([IDMATCH], [TIMESCORE], [SCORE_A], [SCORE_B], [PLAYER_A], [PLAYER_B]) VALUES (N'GG', N'75''', 1, 0, N'Otar Kakabadze', NULL)
INSERT [dbo].[DETAILS_SCORE] ([IDMATCH], [TIMESCORE], [SCORE_A], [SCORE_B], [PLAYER_A], [PLAYER_B]) VALUES (N'GG', N'78''', 1, 1, NULL, N'Khvicha Kvaratskhelia')
INSERT [dbo].[DETAILS_SCORE] ([IDMATCH], [TIMESCORE], [SCORE_A], [SCORE_B], [PLAYER_A], [PLAYER_B]) VALUES (N'GN', N'42''', 0, 1, NULL, N'Steven Berghuis')
INSERT [dbo].[DETAILS_SCORE] ([IDMATCH], [TIMESCORE], [SCORE_A], [SCORE_B], [PLAYER_A], [PLAYER_B]) VALUES (N'GN', N'55''', 0, 2, NULL, N'Luuk de Jong')
INSERT [dbo].[DETAILS_SCORE] ([IDMATCH], [TIMESCORE], [SCORE_A], [SCORE_B], [PLAYER_A], [PLAYER_B]) VALUES (N'GN', N'61''', 0, 3, NULL, N'Memphis Depay')
INSERT [dbo].[DETAILS_SCORE] ([IDMATCH], [TIMESCORE], [SCORE_A], [SCORE_B], [PLAYER_A], [PLAYER_B]) VALUES (N'GN', N'62''', 0, 4, NULL, N'Georginio Wijnaldum')
INSERT [dbo].[DETAILS_SCORE] ([IDMATCH], [TIMESCORE], [SCORE_A], [SCORE_B], [PLAYER_A], [PLAYER_B]) VALUES (N'GN', N'64''', 0, 5, NULL, N'Donyell Malen')
INSERT [dbo].[DETAILS_SCORE] ([IDMATCH], [TIMESCORE], [SCORE_A], [SCORE_B], [PLAYER_A], [PLAYER_B]) VALUES (N'GN', N'85''', 0, 6, NULL, N'Donny van de Beek')
INSERT [dbo].[DETAILS_SCORE] ([IDMATCH], [TIMESCORE], [SCORE_A], [SCORE_B], [PLAYER_A], [PLAYER_B]) VALUES (N'GN', N'88''', 0, 7, NULL, N'Memphis Depay')
INSERT [dbo].[DETAILS_SCORE] ([IDMATCH], [TIMESCORE], [SCORE_A], [SCORE_B], [PLAYER_A], [PLAYER_B]) VALUES (N'UK', N'20''', 1, 0, N'Roman Yaremchuk', NULL)
INSERT [dbo].[DETAILS_SCORE] ([IDMATCH], [TIMESCORE], [SCORE_A], [SCORE_B], [PLAYER_A], [PLAYER_B]) VALUES (N'UK', N'59''', 1, 1, NULL, N'Serikzhan Muzhikov')
INSERT [dbo].[GROUP_MATCH] ([GROUPID], [GROUPNAME]) VALUES (N'ENGCS', N'ENGLAND - CHAMPIONSHIP')
INSERT [dbo].[GROUP_MATCH] ([GROUPID], [GROUPNAME]) VALUES (N'ENGL1', N'ENGLAND - LEAGUGE1')
INSERT [dbo].[GROUP_MATCH] ([GROUPID], [GROUPNAME]) VALUES (N'SPLGSB', N'SPAIN - LALIGA SMARTBANK')
INSERT [dbo].[GROUP_MATCH] ([GROUPID], [GROUPNAME]) VALUES (N'WCUEFAQ1GA', N'WORLD CUP - UEFA QUALIFICATION: 1ST ROUND - GROUP A')
INSERT [dbo].[GROUP_MATCH] ([GROUPID], [GROUPNAME]) VALUES (N'WCUEFAQ1GB', N'WORLD CUP - UEFA QUALIFICATION: 1ST ROUND - GROUP B')
INSERT [dbo].[GROUP_MATCH] ([GROUPID], [GROUPNAME]) VALUES (N'WCUEFAQ1GC', N'WORLD CUP - UEFA QUALIFICATION: 1ST ROUND - GROUP C')
INSERT [dbo].[GROUP_MATCH] ([GROUPID], [GROUPNAME]) VALUES (N'WCUEFAQ1GD', N'WORLD CUP - UEFA QUALIFICATION: 1ST ROUND - GROUP D')
INSERT [dbo].[GROUP_MATCH] ([GROUPID], [GROUPNAME]) VALUES (N'WCUEFAQ1GE', N'WORLD CUP - UEFA QUALIFICATION: 1ST ROUND - GROUP E')
INSERT [dbo].[GROUP_MATCH] ([GROUPID], [GROUPNAME]) VALUES (N'WCUEFAQ1GF', N'WORLD CUP - UEFA QUALIFICATION: 1ST ROUND - GROUP F')
INSERT [dbo].[GROUP_MATCH] ([GROUPID], [GROUPNAME]) VALUES (N'WCUEFAQ1GG', N'WORLD CUP - UEFA QUALIFICATION: 1ST ROUND - GROUP G')
INSERT [dbo].[GROUP_MATCH] ([GROUPID], [GROUPNAME]) VALUES (N'WCUEFAQ1GH', N'WORLD CUP - UEFA QUALIFICATION: 1ST ROUND - GROUP H')
INSERT [dbo].[GROUP_MATCH] ([GROUPID], [GROUPNAME]) VALUES (N'WCUEFAQ1GI', N'WORLD CUP - UEFA QUALIFICATION: 1ST ROUND - GROUP I')
INSERT [dbo].[GROUP_MATCH] ([GROUPID], [GROUPNAME]) VALUES (N'WCUEFAQ1GJ', N'WORLD CUP - UEFA QUALIFICATION: 1ST ROUND - GROUP J')
INSERT [dbo].[MATCH] ([ID], [ID_TEAMA], [ID_TEAMB], [ID_GROUP], [STARTTIME], [STATUS_MATCH]) VALUES (N'AS', N'AZE', N'SER', N'WCUEFAQ1GA', CAST(N'2021-03-30 00:00:00.000' AS DateTime), N'FT')
INSERT [dbo].[MATCH] ([ID], [ID_TEAMA], [ID_TEAMB], [ID_GROUP], [STARTTIME], [STATUS_MATCH]) VALUES (N'BB', N'BEL', N'BLA', N'WCUEFAQ1GE', CAST(N'2021-03-31 00:00:00.000' AS DateTime), N'FT')
INSERT [dbo].[MATCH] ([ID], [ID_TEAMA], [ID_TEAMB], [ID_GROUP], [STARTTIME], [STATUS_MATCH]) VALUES (N'CS', N'CYP', N'SLO', N'WCUEFAQ1GH', CAST(N'2021-03-30 00:00:00.000' AS DateTime), N'FT')
INSERT [dbo].[MATCH] ([ID], [ID_TEAMA], [ID_TEAMB], [ID_GROUP], [STARTTIME], [STATUS_MATCH]) VALUES (N'GG', N'GRE', N'GEO', N'WCUEFAQ1GB', CAST(N'2021-04-01 00:00:00.000' AS DateTime), N'FT')
INSERT [dbo].[MATCH] ([ID], [ID_TEAMA], [ID_TEAMB], [ID_GROUP], [STARTTIME], [STATUS_MATCH]) VALUES (N'GN', N'GIB', N'NET', N'WCUEFAQ1GG', CAST(N'2021-03-31 00:00:00.000' AS DateTime), N'FT')
INSERT [dbo].[MATCH] ([ID], [ID_TEAMA], [ID_TEAMB], [ID_GROUP], [STARTTIME], [STATUS_MATCH]) VALUES (N'UK', N'UKR', N'KAZ', N'WCUEFAQ1GD', CAST(N'2021-04-01 00:00:00.000' AS DateTime), N'FT')
INSERT [dbo].[TEAM] ([IDTEAM], [NAME]) VALUES (N'AZE', N'Azerbaijan')
INSERT [dbo].[TEAM] ([IDTEAM], [NAME]) VALUES (N'BEL', N'Belgium')
INSERT [dbo].[TEAM] ([IDTEAM], [NAME]) VALUES (N'BLA', N'Belarus')
INSERT [dbo].[TEAM] ([IDTEAM], [NAME]) VALUES (N'CYP', N'Cyprus')
INSERT [dbo].[TEAM] ([IDTEAM], [NAME]) VALUES (N'GEO', N'Georgia')
INSERT [dbo].[TEAM] ([IDTEAM], [NAME]) VALUES (N'GIB', N'Gibraltar')
INSERT [dbo].[TEAM] ([IDTEAM], [NAME]) VALUES (N'GRE', N'Greece')
INSERT [dbo].[TEAM] ([IDTEAM], [NAME]) VALUES (N'KAZ', N'Kazakhstan')
INSERT [dbo].[TEAM] ([IDTEAM], [NAME]) VALUES (N'NET', N'Netherlands')
INSERT [dbo].[TEAM] ([IDTEAM], [NAME]) VALUES (N'SER', N'Serbia')
INSERT [dbo].[TEAM] ([IDTEAM], [NAME]) VALUES (N'SLO', N'Slovenia')
INSERT [dbo].[TEAM] ([IDTEAM], [NAME]) VALUES (N'UKR', N'Ukraine')
INSERT [dbo].[USERS] ([USR], [PWD], [LOGINSTATUS]) VALUES (N'admin', N'admin', 0)
INSERT [dbo].[USERS] ([USR], [PWD], [LOGINSTATUS]) VALUES (N'anhkiet', N'191', 0)
INSERT [dbo].[USERS] ([USR], [PWD], [LOGINSTATUS]) VALUES (N'bahuy', N'420', 0)
INSERT [dbo].[USERS] ([USR], [PWD], [LOGINSTATUS]) VALUES (N'user', N'123', 0)
ALTER TABLE [dbo].[DETAILS_CARD]  WITH CHECK ADD  CONSTRAINT [FK_MATCH_CARD] FOREIGN KEY([IDMATCH])
REFERENCES [dbo].[MATCH] ([ID])
GO
ALTER TABLE [dbo].[DETAILS_CARD] CHECK CONSTRAINT [FK_MATCH_CARD]
GO
ALTER TABLE [dbo].[DETAILS_SCORE]  WITH CHECK ADD  CONSTRAINT [FK_MATCH_SCORE] FOREIGN KEY([IDMATCH])
REFERENCES [dbo].[MATCH] ([ID])
GO
ALTER TABLE [dbo].[DETAILS_SCORE] CHECK CONSTRAINT [FK_MATCH_SCORE]
GO
ALTER TABLE [dbo].[MATCH]  WITH CHECK ADD  CONSTRAINT [FK_MATCH_GROUP] FOREIGN KEY([ID_GROUP])
REFERENCES [dbo].[GROUP_MATCH] ([GROUPID])
GO
ALTER TABLE [dbo].[MATCH] CHECK CONSTRAINT [FK_MATCH_GROUP]
GO
ALTER TABLE [dbo].[MATCH]  WITH CHECK ADD  CONSTRAINT [FK_TEAM_MATCH_A] FOREIGN KEY([ID_TEAMA])
REFERENCES [dbo].[TEAM] ([IDTEAM])
GO
ALTER TABLE [dbo].[MATCH] CHECK CONSTRAINT [FK_TEAM_MATCH_A]
GO
ALTER TABLE [dbo].[MATCH]  WITH CHECK ADD  CONSTRAINT [FK_TEAM_MATCH_B] FOREIGN KEY([ID_TEAMB])
REFERENCES [dbo].[TEAM] ([IDTEAM])
GO
ALTER TABLE [dbo].[MATCH] CHECK CONSTRAINT [FK_TEAM_MATCH_B]
GO
ALTER TABLE [dbo].[DETAILS_CARD]  WITH CHECK ADD  CONSTRAINT [C_CATEGORY] CHECK  (([CATEGORY] like 'RED' OR [CATEGORY] like 'YELLOW'))
GO
ALTER TABLE [dbo].[DETAILS_CARD] CHECK CONSTRAINT [C_CATEGORY]
GO
ALTER TABLE [dbo].[DETAILS_CARD]  WITH CHECK ADD  CONSTRAINT [C_PLAYER] CHECK  (([TIMECARD] IS NOT NULL AND ([PLAYER_A] IS NOT NULL AND [PLAYER_B] IS NULL OR [PLAYER_A] IS NULL AND [PLAYER_B] IS NOT NULL)))
GO
ALTER TABLE [dbo].[DETAILS_CARD] CHECK CONSTRAINT [C_PLAYER]
GO
ALTER TABLE [dbo].[DETAILS_SCORE]  WITH CHECK ADD  CONSTRAINT [C_PLAYER_A_B] CHECK  (([TIMESCORE] IS NOT NULL AND ([PLAYER_A] IS NOT NULL AND [PLAYER_B] IS NULL) OR [PLAYER_A] IS NULL AND [PLAYER_B] IS NOT NULL))
GO
ALTER TABLE [dbo].[DETAILS_SCORE] CHECK CONSTRAINT [C_PLAYER_A_B]
GO
ALTER TABLE [dbo].[MATCH]  WITH CHECK ADD  CONSTRAINT [C_TEAM] CHECK  ((NOT [ID_TEAMA]=[ID_TEAMB]))
GO
ALTER TABLE [dbo].[MATCH] CHECK CONSTRAINT [C_TEAM]
GO
ALTER TABLE [dbo].[MATCH]  WITH CHECK ADD  CONSTRAINT [C_TIME] CHECK  ((datediff(minute,[STARTTIME],getdate())>(90) AND [STATUS_MATCH]='FT' OR datediff(minute,[STARTTIME],getdate())=(45) AND [STATUS_MATCH]='HT' OR (datediff(minute,[STARTTIME],getdate())<(90) OR datediff(minute,[STARTTIME],getdate())>(0)) AND NOT datediff(minute,[STARTTIME],getdate())=(45) AND [STATUS_MATCH]='PL'))
GO
ALTER TABLE [dbo].[MATCH] CHECK CONSTRAINT [C_TIME]
GO
