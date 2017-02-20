object MainForm: TMainForm
  Left = 206
  Top = 150
  BorderIcons = [biSystemMenu, biMinimize]
  BorderStyle = bsSingle
  Caption = #1056#1077#1074#1080#1079#1086#1088' '
  ClientHeight = 137
  ClientWidth = 457
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  Menu = MainMenu1
  OldCreateOrder = False
  OnCreate = FormCreate
  OnDestroy = FormDestroy
  DesignSize = (
    457
    137)
  PixelsPerInch = 96
  TextHeight = 13
  object LabelConnection: TLabel
    Left = 112
    Top = 13
    Width = 3
    Height = 13
  end
  object Bevel1: TBevel
    Left = 0
    Top = 0
    Width = 457
    Height = 2
    Anchors = [akLeft, akTop, akRight]
    Shape = bsFrame
  end
  object ConnectBtn: TButton
    Left = 8
    Top = 8
    Width = 97
    Height = 25
    Caption = #1055#1086#1076#1082#1083#1102#1095#1080#1090#1100#1089#1103
    TabOrder = 0
    OnClick = ConnectBtnClick
  end
  object InspListBox: TComboBox
    Left = 8
    Top = 40
    Width = 441
    Height = 21
    Anchors = [akLeft, akTop, akRight]
    Enabled = False
    ItemHeight = 13
    TabOrder = 1
    OnChange = InspListBoxChange
    OnKeyPress = InspListBoxKeyPress
    OnSelect = InspListBoxSelect
  end
  object AddBtn: TButton
    Left = 184
    Top = 72
    Width = 129
    Height = 25
    Caption = #1044#1086#1073#1072#1074#1080#1090#1100' '#1088#1077#1074#1080#1079#1086#1088#1072
    Enabled = False
    TabOrder = 3
    OnClick = AddBtnClick
  end
  object InputBtn: TButton
    Left = 8
    Top = 104
    Width = 169
    Height = 25
    Caption = #1042#1085#1077#1089#1090#1080' '#1087#1088#1086#1090#1086#1082#1086#1083' '#1087#1088#1086#1074#1077#1088#1082#1080
    Enabled = False
    TabOrder = 5
    OnClick = InputBtnClick
  end
  object JournalBtn: TButton
    Left = 184
    Top = 104
    Width = 129
    Height = 25
    Caption = #1046#1091#1088#1085#1072#1083
    Enabled = False
    TabOrder = 6
    OnClick = JournalBtnClick
  end
  object ReportBtn: TButton
    Left = 320
    Top = 104
    Width = 129
    Height = 25
    Caption = #1043#1086#1076#1086#1074#1086#1081' '#1086#1090#1095#1077#1090
    Enabled = False
    TabOrder = 7
    OnClick = ReportBtnClick
  end
  object EnterBtn: TButton
    Left = 8
    Top = 72
    Width = 169
    Height = 25
    Caption = #1040#1074#1090#1086#1088#1080#1079#1072#1094#1080#1103
    TabOrder = 2
    OnClick = EnterBtnClick
  end
  object DelBtn: TButton
    Left = 320
    Top = 72
    Width = 129
    Height = 25
    Enabled = False
    TabOrder = 4
  end
  object MainMenu1: TMainMenu
    Left = 424
    Top = 8
    object MMFile: TMenuItem
      Caption = #1060#1072#1081#1083
      object MMConnect: TMenuItem
        Caption = #1055#1086#1076#1082#1083#1102#1095#1080#1090#1100#1089#1103
        OnClick = ConnectBtnClick
      end
      object MMOptions: TMenuItem
        Caption = #1053#1072#1089#1090#1088#1086#1081#1082#1080
        OnClick = MMOptionsClick
      end
      object MMExit: TMenuItem
        Caption = #1042#1099#1093#1086#1076
        OnClick = MMExitClick
      end
    end
    object MMAbout: TMenuItem
      Caption = #1054' '#1087#1088#1086#1075#1088#1072#1084#1084#1077
      OnClick = MMAboutClick
    end
  end
end
