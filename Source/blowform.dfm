object Form1: TForm1
  Left = 382
  Top = 665
  Width = 409
  Height = 223
  Caption = 'Form1'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object Shape1: TShape
    Left = 328
    Top = 152
    Width = 41
    Height = 33
    Shape = stCircle
  end
  object Label1: TLabel
    Left = 40
    Top = 29
    Width = 21
    Height = 13
    Caption = 'KEY'
  end
  object Label2: TLabel
    Left = 28
    Top = 61
    Width = 33
    Height = 13
    Caption = 'INPUT'
  end
  object Label3: TLabel
    Left = 8
    Top = 93
    Width = 53
    Height = 13
    Caption = 'ENCODED'
  end
  object Label4: TLabel
    Left = 8
    Top = 125
    Width = 53
    Height = 13
    Caption = 'DECODED'
  end
  object Label5: TLabel
    Left = 72
    Top = 8
    Width = 29
    Height = 13
    Caption = 'DATA'
  end
  object Label6: TLabel
    Left = 345
    Top = 8
    Width = 44
    Height = 13
    Caption = 'LENGTH'
  end
  object KeyData: TEdit
    Left = 72
    Top = 24
    Width = 265
    Height = 22
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'Courier New'
    Font.Style = []
    ParentFont = False
    TabOrder = 0
  end
  object input: TEdit
    Left = 72
    Top = 56
    Width = 265
    Height = 22
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'Courier New'
    Font.Style = []
    ParentFont = False
    TabOrder = 1
  end
  object Encoded: TEdit
    Left = 72
    Top = 88
    Width = 265
    Height = 22
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'Courier New'
    Font.Style = []
    ParentFont = False
    TabOrder = 2
  end
  object Decoded: TEdit
    Left = 72
    Top = 120
    Width = 265
    Height = 22
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'Courier New'
    Font.Style = []
    ParentFont = False
    TabOrder = 3
  end
  object Button1: TButton
    Left = 160
    Top = 160
    Width = 75
    Height = 25
    Caption = 'Button1'
    TabOrder = 4
    OnClick = Button1Click
  end
  object Edit1: TEdit
    Left = 345
    Top = 24
    Width = 41
    Height = 21
    TabOrder = 5
  end
  object Edit2: TEdit
    Left = 345
    Top = 56
    Width = 41
    Height = 21
    TabOrder = 6
  end
  object Edit3: TEdit
    Left = 345
    Top = 88
    Width = 41
    Height = 21
    TabOrder = 7
  end
  object Edit4: TEdit
    Left = 345
    Top = 120
    Width = 41
    Height = 21
    TabOrder = 8
  end
end
