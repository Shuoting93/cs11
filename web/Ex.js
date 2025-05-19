// src/ExhibitionTable.js
import React, { useEffect, useState } from 'react';
import { DataGrid } from '@mui/x-data-grid';
import { TextField, Container, Typography } from '@mui/material';

export default function ExhibitionTable() {
  const [allData, setAllData] = useState([]);
  const [searchKeyword, setSearchKeyword] = useState('');

  // ✅ 一開始出現就自動抓 API 的資料（這就是 useEffect）
  useEffect(() => {
    fetch("https://cloud.culture.tw/frontsite/trans/SearchShowAction.do?method=doFindTypeJ&category=6")
      .then(res => res.json())
      .then(data => {
        const formatted = data.map((d, i) => ({
          id: i,
          title: d.title || '（無標題）',
          location: d.showInfo?.[0]?.location || '（無地點）',
          price: d.showInfo?.[0]?.price || '（無票價）',
        }));
        setAllData(formatted);
      });
  }, []); // 👈 這裡的 [] 表示只在「第一次載入」時執行

  // 🔍 關鍵字過濾
  const filteredRows = allData.filter((row) =>
    row.title.includes(searchKeyword)
  );

  const columns = [
    { field: 'title', headerName: '名稱', flex: 1 },
    { field: 'location', headerName: '地點', flex: 1 },
    { field: 'price', headerName: '票價', flex: 1 },
  ];

  return (
    <Container>
      <Typography variant="h4" gutterBottom>景點觀光展覽資訊</Typography>
      <TextField
        label="輸入展覽名稱關鍵字"
        variant="outlined"
        fullWidth
        margin="normal"
        onChange={(e) => setSearchKeyword(e.target.value)}
      />
      <div style={{ height: 600, width: '100%' }}>
        <DataGrid
          rows={filteredRows}
          columns={columns}
          pageSize={10}
          rowsPerPageOptions={[10]}
        />
      </div>
    </Container>
  );
}
