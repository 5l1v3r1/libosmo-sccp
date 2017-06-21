#pragma once

#include <osmocom/sigtran/osmo_ss7.h>
#include <osmocom/sigtran/xua_msg.h>

struct osmo_sccp_addr;
struct m3ua_data_hdr;

int sua_addr_parse_part(struct osmo_sccp_addr *out,
			const struct xua_msg_part *param);
int sua_addr_parse(struct osmo_sccp_addr *out, struct xua_msg *xua, uint16_t iei);

int sua_parse_gt(struct osmo_sccp_gt *gt, const uint8_t *data, unsigned int datalen);

struct xua_msg *osmo_sccp_to_xua(struct msgb *msg);
struct msgb *osmo_sua_to_sccp(struct xua_msg *xua);

int sua_rx_msg(struct osmo_ss7_asp *asp, struct msgb *msg);

int sua_tx_xua_as(struct osmo_ss7_as *as, struct xua_msg *xua);

struct osmo_mtp_prim *m3ua_to_xfer_ind(struct xua_msg *xua);
int m3ua_hmdc_rx_from_l2(struct osmo_ss7_instance *inst, struct xua_msg *xua);
int m3ua_tx_xua_as(struct osmo_ss7_as *as, struct xua_msg *xua);
int m3ua_rx_msg(struct osmo_ss7_asp *asp, struct msgb *msg);

struct msgb *m3ua_msgb_alloc(const char *name);
struct xua_msg *m3ua_xfer_from_data(const struct m3ua_data_hdr *data_hdr,
				    const uint8_t *data, unsigned int data_len);
struct m3ua_data_hdr *data_hdr_from_m3ua(struct xua_msg *xua);
void m3ua_dh_to_xfer_param(struct osmo_mtp_transfer_param *param,
			   const struct m3ua_data_hdr *mdh);
void mtp_xfer_param_to_m3ua_dh(struct m3ua_data_hdr *mdh,
				const struct osmo_mtp_transfer_param *param);


extern const struct xua_msg_class m3ua_msg_class_mgmt;
extern const struct xua_msg_class m3ua_msg_class_snm;
extern const struct xua_msg_class m3ua_msg_class_rkm;
extern const struct xua_msg_class m3ua_msg_class_aspsm;
extern const struct xua_msg_class m3ua_msg_class_asptm;

extern const struct value_string m3ua_err_names[];
extern const struct value_string m3ua_ntfy_type_names[];
extern const struct value_string m3ua_ntfy_stchg_names[];
extern const struct value_string m3ua_ntfy_other_names[];

struct xua_msg *m3ua_encode_notify(const struct osmo_xlm_prim_notify *npar);
int m3ua_decode_notify(struct osmo_xlm_prim_notify *npar, void *ctx,
			const struct xua_msg *xua);
int m3ua_rx_rkm(struct osmo_ss7_asp *asp, struct xua_msg *xua);
void xua_rkm_cleanup_dyn_as_for_asp(struct osmo_ss7_asp *asp);

struct osmo_xlm_prim *xua_xlm_prim_alloc(enum osmo_xlm_prim_type prim_type,
					 enum osmo_prim_operation op);

void xua_asp_send_xlm_prim(struct osmo_ss7_asp *asp, struct osmo_xlm_prim *prim);
void xua_asp_send_xlm_prim_simple(struct osmo_ss7_asp *asp,
				enum osmo_xlm_prim_type prim_type,
				enum osmo_prim_operation op);

extern struct osmo_fsm xua_default_lm_fsm;
extern const struct value_string m3ua_rkm_reg_status_vals[];
extern const struct value_string m3ua_rkm_dereg_status_vals[];

#define CS7_STR	"ITU-T Signaling System 7\n"
#define PC_STR	"Point Code\n"
#define INST_STR "An instance of the SS7 stack\n"

int xua_as_transmit_msg(struct osmo_ss7_as *as, struct msgb *msg);


int ipa_tx_xua_as(struct osmo_ss7_as *as, struct xua_msg *xua);
int ipa_rx_msg(struct osmo_ss7_asp *asp, struct msgb *msg);

int osmo_isup_party_parse(char *out_digits, const uint8_t *in,
			unsigned int in_num_bytes, bool odd);
int osmo_sccp_addr_parse(struct osmo_sccp_addr *out,
			const uint8_t *addr, unsigned int addrlen);
