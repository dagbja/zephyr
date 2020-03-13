/*
 * Copyright (c) 2018-2019 Nordic Semiconductor ASA
 *
 * SPDX-License-Identifier: Apache-2.0
 */

static inline struct pdu_adv *lll_adv_pdu_latest_get(struct lll_adv_pdu *pdu,
						     u8_t *is_modified)
{
	u8_t first;

	first = pdu->first;
	if (first != pdu->last) {
		first += 1U;
		if (first == DOUBLE_BUFFER_SIZE) {
			first = 0U;
		}
		pdu->first = first;
		*is_modified = 1U;
	}

	return (void *)pdu->pdu[first];
}

static inline struct pdu_adv *lll_adv_data_latest_get(struct lll_adv *lll,
						      u8_t *is_modified)
{
	return lll_adv_pdu_latest_get(&lll->adv_data, is_modified);
}

static inline struct pdu_adv *lll_adv_scan_rsp_latest_get(struct lll_adv *lll,
							  u8_t *is_modified)
{
	return lll_adv_pdu_latest_get(&lll->scan_rsp, is_modified);
}

static inline struct pdu_adv *lll_adv_data_curr_get(struct lll_adv *lll)
{
	return (void *)lll->adv_data.pdu[lll->adv_data.first];
}

static inline struct pdu_adv *lll_adv_scan_rsp_curr_get(struct lll_adv *lll)
{
	return (void *)lll->scan_rsp.pdu[lll->scan_rsp.first];
}

#if defined(CONFIG_BT_CTLR_ADV_EXT)
static inline struct pdu_adv *lll_adv_aux_data_latest_get(struct lll_adv *lll,
							  u8_t *is_modified)
{
	return lll_adv_pdu_latest_get(&lll->aux_data, is_modified);
}

static inline struct pdu_adv *lll_adv_aux_data_curr_get(struct lll_adv *lll)
{
	return (void *)lll->aux_data.pdu[lll->aux_data.first];
}

#if defined(CONFIG_BT_CTLR_ADV_PERIODIC)
static inline struct pdu_adv *
lll_adv_sync_data_latest_get(struct lll_adv_sync *lll, u8_t *is_modified)
{
	return lll_adv_pdu_latest_get(&lll->data, is_modified);
}

static inline struct pdu_adv *
lll_adv_sync_data_curr_get(struct lll_adv_sync *lll)
{
	return (void *)lll->data.pdu[lll->data.first];
}
#endif /* CONFIG_BT_CTLR_ADV_PERIODIC */
#endif /* CONFIG_BT_CTLR_ADV_EXT */
